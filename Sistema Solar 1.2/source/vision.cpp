#define _USE_MATH_DEFINES
#include <cmath>

#include "vision.h"
#include <GL/glu.h>	

#define DIST_CAMARA 5
#define INCREMENTO 0.1

float alpha;    // Angulo con respecto a y (anchura)
float beta;     // Angulo con respecto a x (altura)

float fovy = 45;

//camara por defecto en modo voayager
int camara = 1;

// TODO: -REVISAR EL INCREMENTO
//       -CONTROLAR QUE VUELVA A CERO SI REALIZA LA VUELTA COMPLETA
//       -CAMBIAR VALORES DE LOOK AT Y DEL ORTHO
//       -CAMBIAR EL NEAR Y EL FAR EN LA FUNCION CHANGE SIZE 




void Camara(int w, int h) {

    //relacion de aspecto entre el ancho y el alto de la ventana
    float aspecto = (float)w / (float)h;

    //configuramos la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);

    //matriz identidad
    glLoadIdentity();

    // realizamos el ortho para la multivista
    // left,right,bottom,top,near,far)
    glOrtho(-3 * aspecto, 3 * aspecto, -3, 3, 0.1, DIST_CAMARA);

    //colocamos la camara en la posicion deseada
    //gluLookAt(((float)DISTANCIA * (float)sin(alpha) * cos(beta)), ((float)DISTANCIA * (float)sin(beta)), ((float)DISTANCIA * cos(alpha) * cos(beta)), 0, 0, 0, 0, cos(beta), 0);

    gluLookAt(
        (GLdouble)DIST_CAMARA * cos(alpha) * (M_PI / 180), (GLdouble)DIST_CAMARA * sin(beta) * (M_PI / 180), (GLdouble)(-1) * DIST_CAMARA * sin(alpha) * (M_PI / 180),
        0, 0, 0,
        0, 1, 0
    );

}

void teclasEspeciales(int cursor) {

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
            alpha -= INCREMENTO;
            break;
        //izquierda
        case GLUT_KEY_LEFT:
            alpha += INCREMENTO;
            break;
        //en otro caso
        default:
            break;


        /*Control para que no se pase de 360*/

        //volvemos a lanzar
        glutPostRedisplay();
    
    }

}

void changeSize(GLint newWidth, GLint newHeight) {

    //configuramos el viewport
    
    glViewport(0, 0, newWidth, newHeight);

    //configuramos la matriz de proyeccion y la matriz identidad
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //configuramos la perspectiva (fovy,relacion de aspecto,near,far)
    
    gluPerspective(fovy, (float)newWidth / (float)newHeight, 1.0, 500);
}

/*
 * Caso camara, manejar
 * Caso de planetas: le pasamos el nombre y hacemos sis.planetas()[nombre_planeta]
 *      Y obtenemos los datos de ese planeta
*/

void onMenu(int opcion) {

    //en funcion del valor de la camara hacemos el telescopio correspondiente.
    switch (opcion) {
        case 1:
            camara = 1;
            break;
        case 2:
            camara = 2;
            break;
        case 3:
            camara = 3;
            break;
        case 4:
            camara = 4;
            break;
        case 5:
            camara = 5;
            break;
        case 6:
            camara = 6;
            break;
        case 7:
            camara = 7;
            break;
        case 8:
            camara = 8;
            break;
        case 9:
            camara = 9;
            break;

        case 10:
            camara = 10;
            break;

        case 11:
            camara = 11;
            break;
        }
    glutPostRedisplay();
}


void menu(void) {
    int menuFondo;

    //creamos el menu
    menuFondo = glutCreateMenu(onMenu);

    //añadimos las entradas
    glutAddMenuEntry("Voyayer", 1);

    int index = 1;

    /*
    * Crear las entradas de forma dinamica
    for (std::string nombre_planeta : sis.showPlanetas()) {
        glutAddMenuEntry(nombre_planeta, index++);
        planetas.push_back(nombre_planeta);
    }
    */


    glutAddMenuEntry("Sol", 2);
    glutAddMenuEntry("Mercurio", 3);
    glutAddMenuEntry("Venus", 4);
    glutAddMenuEntry("Marte", 5);
    glutAddMenuEntry("Jupiter", 6);
    glutAddMenuEntry("Saturno", 7);
    glutAddMenuEntry("Urano", 8);
    glutAddMenuEntry("Neptuno", 9);
    glutAddMenuEntry("Luna", 10);
    glutAddMenuEntry("ISS", 11);
    
    //configuramos el boton que permite realizar esto al click derecho
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

