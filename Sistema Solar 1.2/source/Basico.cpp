
/*****************************************************
Autores: Ivan Quintáns González y Cristian Novoa Gonzalez
Practica 4 Sistema Solar 1.2
*************************************************************/


#include <windows.h>		// Inclusión de variables de Windows
#include "glut.h"			// Inclusión de librerías GLUT 
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliare
#include "Sistema.h"


const int W_WIDTH = 600;	 //Ancho de la ventana
const int W_HEIGHT = 600;		//Alto de la ventana

//declaracion de los objetos de nuestro sistema solar


//{distancia,vel_trans,ang_rot,vel_rot,ang_rot,tam
	//listarender,color1,color2,colro3}

objeto sol = { 0,0,0,10,0,100,0,1,1,0 };
objeto mercurio = { 200,5.3,0,50,0,50,0,1,0,0 };
objeto venus = { 350,8,0,30,0,50,0,0,1,0 };
objeto luna = { 100,9,0,10,0,20,0,1,0,0 };
objeto tierra = { 600,5,0,10,0,80,0,0,0,1 };
objeto jupiter = { 900,6,0,60,0,60,0,0,0,1 };
objeto marte = { 800,2,0,10,0,30,0,0,0,1 };
objeto saturno = { 1100,4,0,20,0,50,0,1,0,0 };
objeto urano = { 1250,3,0,40,0,30,0,0,1,0 };
objeto neptuno = { 1350,4.5,0,10,0,50,0,0,0,1 };

// Función de dibujo
void Display(void) {
	// Limpia los buffer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();// Intercambia los buffers gráficos disponibles
	
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	
	// Inicializa las GLUT
	glutInit(&argc, argv);

	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	// Fija el tamaño de la ventana
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	
	// Fija la posición de la ventana
	glutInitWindowPosition(100, 100);
	
	// Permite poner nombre a la ventana en la barra de título.
	glutCreateWindow("Sistema Solar 1.2");

	// Inicializa la visualización
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Fija el negro como color de borrado
	
	glClearDepth(1.0);				//Valor de limpieza del z-buffer

	glutDisplayFunc(Display);// Define las funciones de Callback  
	glutMainLoop(); // Inicia el lazo de visualización.
	return 0;
}