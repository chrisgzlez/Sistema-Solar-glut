#define _USE_MATH_DEFINES
#include <cmath>

#include <vision.h>
#include <GL/glu.h>	
#include <iostream>
#include <Planeta.h>
#include <Sistema.h>
#include <string.h>

#define DIST_CAMARA 4000
#define INCREMENTO M_PI/90 // 2 grados en radianes
#define SIZE_SPACE 3000
#define FAR 10000
#define NEAR 1  

float alpha;    // Angulo con respecto a y (anchura)
float beta;     // Angulo con respecto a x (altura)

float fovy = 45;


// Varible global usada para redefinir la perspectiva y el ratio de aspecto de los objetos
float aspecto;

// TODO: -REVISAR EL INCREMENTO
//       -CONTROLAR QUE VUELVA A CERO SI REALIZA LA VUELTA COMPLETA
//       -CAMBIAR VALORES DE LOOK AT Y DEL ORTHO
//       -CAMBIAR EL NEAR Y EL FAR EN LA FUNCION CHANGE SIZE 

void Camara() {

    //configuramos la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);

    //matriz identidad
    glLoadIdentity();

    // realizamos el ortho para la multivista
    // left,right,bottom,top,near,far)
    // Define el tamaño del espacio
    glOrtho(-SIZE_SPACE * aspecto, SIZE_SPACE * aspecto, -SIZE_SPACE, SIZE_SPACE, NEAR, FAR);

    // Define la posicion del observador, su punto de referencia y su vector up
    gluLookAt(
        (GLdouble)DIST_CAMARA * cos(alpha) * cos(beta), (GLdouble)DIST_CAMARA * sin(beta), (GLdouble)(-1) * DIST_CAMARA * sin(alpha) * cos(beta),
        0, 0, 0,
        0, cos(beta), 0
    );
}

void teclasEspeciales(int cursor, int x, int y) {

    //en funcion del cursor
    switch (cursor) {
        //arriba
        case GLUT_KEY_UP:
            beta += INCREMENTO;
            break;
        //abajo
        case GLUT_KEY_DOWN:
            beta -= INCREMENTO;
            break;
        //derecha
        case GLUT_KEY_RIGHT:
            alpha += INCREMENTO;
            break;
        //izquierda
        case GLUT_KEY_LEFT:
            alpha -= INCREMENTO;
            break;
        //en otro caso
        default:
            break;
    }

    // Evitar overflow
    if (alpha >= 2 * M_PI) alpha -= 2 * M_PI;
    if (alpha <= -2 * M_PI) alpha += 2 * M_PI;
    if (beta >= 2 * M_PI) beta -= 2 * M_PI;
    if (beta <= -2 * M_PI) beta += 2 * M_PI;


    //volvemos a lanzar
    glutPostRedisplay();

}

void changeSize(GLint newWidth, GLint newHeight) {

    aspecto = (float)newWidth / (float)newHeight;

    //configuramos el viewport
    glViewport(0, 0, newWidth, newHeight);

    //configuramos la matriz de proyeccion y la matriz identidad
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //configuramos la perspectiva (fovy,relacion de aspecto,near,far)
    gluPerspective(fovy, (float)newWidth / (float)newHeight, .01, 500.);
}

// TODO: Facer define de near e far
void telescopio(Planeta& PointOffView, Planeta& PointOffRefference) {

    //configuramos la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);

    //matriz identidad
    glLoadIdentity();

    //tenemos que mirar desde la tierra hasta el planeta que queramos mirar.
    
    gluPerspective(fovy,aspecto, NEAR, FAR);

    //en primer lugar comprobamos si es un satelite.

    //si el pov es un satelite
    if (PointOffView.mainPlaneta() != NULL) {
        gluLookAt(
            (GLdouble)PointOffRefference.dist() * cos((PointOffRefference._angulo_trans * M_PI / 180)) + PointOffView.dist() * cos((PointOffView._angulo_trans + PointOffRefference._angulo_trans) * M_PI / 180),
            0,
            (GLdouble)(-1) * PointOffRefference.dist() * sin(PointOffRefference._angulo_trans * M_PI / 180) - PointOffView.dist() * sin((PointOffView._angulo_trans + PointOffRefference._angulo_trans) * M_PI / 180),

            (GLdouble)(PointOffRefference.dist())* cos(PointOffRefference._angulo_trans * M_PI / 180),
            0,
            (GLdouble)(-1)* (PointOffRefference.dist())* sin(PointOffRefference._angulo_trans * M_PI / 180),

            0, 1, 0);

    }
    else { // Si no es satelite
        gluLookAt(
            (GLdouble)PointOffView.dist() * cos(PointOffView._angulo_trans * M_PI / 180),
            0,
            (GLdouble)(-1)*PointOffView.dist() * sin(PointOffView._angulo_trans * M_PI / 180),

            (GLdouble)PointOffRefference.dist() * cos(PointOffRefference._angulo_trans * M_PI / 180),
            0,
            (GLdouble)(-1)*PointOffRefference.dist() * sin(PointOffRefference._angulo_trans * M_PI / 180),

            0, 1, 0);
    }



}