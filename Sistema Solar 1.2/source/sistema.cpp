#include <camara.h>

//fov
float fovy = 45;

void changeSize(GLint newWidth, GLint newHeight) {

    //configuaramos el view port al ancho y alto nuevo
    glViewport(0, 0, newWidth, newHeight);
    
    //cargamos la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //cambiamos la matriz de proyeccion 
    gluPerspective(fovy, (float)newWidth/(float)newHeight, 1.0, 500);

    //julian no la utiliza ver que hace esta mierda
    glutPostRedisplay();
    
     
}