
/*****************************************************
Autores: Ivan Quintáns González y Cristian Novoa Gonzalez
Practica 4 Sistema Solar 1.2
*************************************************************/


#include <windows.h>		// Inclusión de variables de Windows
#include "glut.h"			// Inclusión de librerías GLUT 
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliare
#include "Sistema.h"
#include "esfera.h"


const int W_WIDTH = 600;	 //Ancho de la ventana
const int W_HEIGHT = 600;		//Alto de la ventana
GLfloat fAngulo, fAngulo2;

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

int index;

void Idle(void) {
	fAngulo += 0.03f;
	if (fAngulo > 360)
		fAngulo -= 360.0f;
	fAngulo2 += 0.1f;
	if (fAngulo > 360)
		fAngulo -= 360.0f;
	glutPostRedisplay();
}


// Función de dibujo
void Display(void) {
	// Limpia los buffer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glPushMatrix();
	glRotatef(0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(fAngulo, 0.0, 1.0, 0.0);
	glScalef(.2, .2, .2);
	glColor3f(1.0, 1.0, 0.);
	glCallList(index);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(fAngulo2, 0.0, 1.0, 0.0);
	glTranslatef(0.6, 0.0, 0.0);
	glPushMatrix();
	glRotatef(0, 0.0, 1.0, 0.0);
	glScalef(.075, .075, .075);
	glColor3f(1.0, 0.0, 0.);
	glCallList(index);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glRotatef(fAngulo, 0.0, 1.0, 0.0);
	glTranslatef(0.8, 0.0, 0.0);
	glPushMatrix();
	glRotatef(0, 0.0, 1.0, 0.0);
	glScalef(.1, .1, .1);
	glColor3f(.0, 1.0, 0.);
	glCallList(index);
	glPopMatrix();
	glPopMatrix();


	/*
	* glPushMatrix();
	glScalef(1., 1., 1.);
	glColor3f(1.0, 1.0, 0.);
	glCallList(index);
	glPopMatrix();
	*/
	

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
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	
	// Fija la posición de la ventana
	glutInitWindowPosition(100, 100);
	
	// Permite poner nombre a la ventana en la barra de título.
	glutCreateWindow("Sistema Solar 1.2");

	// Inicializa la visualización
	openGlInit();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	index = myEsfera();

	glutDisplayFunc(Display);// Define las funciones de Callback  
	glutIdleFunc(Idle);


	glutMainLoop(); // Inicia el lazo de visualización.
	return 0;
}