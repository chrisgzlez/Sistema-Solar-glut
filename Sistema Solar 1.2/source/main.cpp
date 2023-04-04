
/*****************************************************
Autores: Ivan Quintáns González y Cristian Novoa Gonzalez
Practica 4 Sistema Solar 1.2
*************************************************************/

//#include <stdlib.h>         // Necesaria en todos para evitar conflicto con glut
                            // Vease: https://stackoverflow.com/questions/14402/glut-exit-redefinition-error

#include <windows.h>		// Inclusión de variables de Windows
#include "glut.h"			// Inclusión de librerías GLUT 
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliare
#include "esfera.h"
#include "planeta.h"



#include <iostream>

//Tamaño de ventana 
int w = 500;
int h = 500;

GLfloat fAngulo, fAngulo2;
GLuint index_esfera = esfera();

//declaracion de los Planetas de nuestro sistema solar


//{distancia,vel_trans,ang_rot,vel_rot,ang_rot,tam
	//listarender,color1,color2,colro3}

Planeta sol = Planeta( 0,0,0,10,0,100, index_esfera,1,1,0 );
Planeta mercurio = Planeta( 200,5.3,0,50,0,50, index_esfera,1,0,0 );
Planeta venus = Planeta( 350,8,0,30,0,50, index_esfera,0,1,0 );
Planeta luna = Planeta( 100,9,0,10,0,20, index_esfera,1,0,0 );
Planeta tierra = Planeta( 600,5,0,10,0,80, index_esfera,0,0,1 );
Planeta jupiter = Planeta( 900,6,0,60,0,60, index_esfera,0,0,1 );
Planeta marte = Planeta( 800,2,0,10,0,30, index_esfera,0,0,1 );
Planeta saturno = Planeta( 1100,4,0,20,0,50, index_esfera,1,0,0 );
Planeta urano = Planeta( 1250,3,0,40,0,30, index_esfera,0,1,0 );
Planeta neptuno = Planeta( 1350,4.5,0,10,0,50, index_esfera,0,0,1 );

Planeta sol_prueba = Planeta( 0., 0., 0., 0.03, 0., 0.25, 0, 1, 0.78, 0.2 );
Planeta p1 = Planeta( 0.5, 0.03, 0., 0.03, 0., 0.08, 0, 1.f, 0., 0. );
Planeta p2 = Planeta( 0.7, 0.02, 0., 0.02, 0., 0.06, 0, 0., 1.f, 0. );
Planeta p3 = Planeta( 0.9, 0.01, 0., 0.01, 0., 0.03, 0, 0., 0., 1.f );


Planeta sistema[] = { sol_prueba, p1, p2, p3 };
//Planeta sistema[] = { sol_prueba };
int n_planetas = sizeof(sistema) / sizeof(Planeta);


void idle() {
    glutPostRedisplay();
}


// Función de dibujo
void display(void) {
	// Limpia los buffer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < n_planetas; i++) {
        sistema[i].display(index_esfera);
        sistema[i].translate();
        sistema[i].rotate();
    }

	glutSwapBuffers();
	glFlush();// Intercambia los buffers gráficos disponibles
}

void openGlInit() {
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	glClearDepth(1.0f); //Valor z-buffer
	glClearColor(.0f, 0.f, 0.f, .0f);  // valor limpieza buffer color (fondo)
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glCullFace(GL_BACK);

}

int main(int argc, char **argv) {

	// Inicializa las GLUT
	glutInit(&argc, argv);

	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	// Fija el tamaño de la ventana
	glutInitWindowSize(w, h);
	
	// Fija la posición de la ventana
	glutInitWindowPosition(1300, 100);
	
	// Permite poner nombre a la ventana en la barra de título.
	glutCreateWindow("Sistema Solar 1.2");

	// Inicializa la visualización
	openGlInit();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glutDisplayFunc(display);// Define las funciones de Callback  
	glutIdleFunc(idle);
    glutReshapeFunc(changeSize);

  
	glutMainLoop(); // Inicia el lazo de visualización.
	return 0;
}