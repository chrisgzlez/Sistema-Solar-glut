#include <glut.h>
#include <windows.h>		// Inclusi�n de variables de Windows
#include "glut.h"			// Inclusi�n de librer�as GLUT 
#include <GL/gl.h>			// Inclusi�n de librer�as GL
#include <GL/glu.h>			// Inclusi�n de librer�as auxiliare


//
typedef struct planeta{ 
	GLfloat     dist;           // distancia al sol
	GLfloat     vel_trans;      // velocidad de transalacion
	GLfloat     angulo_trans;   // Angulo de transalacion
	GLfloat     vel_rot;        // Velocidad rotacion
	GLfloat     angulo_rot;     // Angulo de rotacion
	GLfloat     size;           // Size del planeta
	GLuint      listarender;    // lista de comandos para genera TODO algo
	
    // colores rgb del planeta
    GLfloat     red;         
	GLfloat     green;
	GLfloat     blue;
} Planeta;

#define CR 0.0175
#define MYTIEMPO 41

void myCamara(int w, int h);

void myTeclasespeciales(int cursor, int x, int y);
void myEjes();
int myEsfera();
void myTelescopio(GLfloat distancia, GLfloat angulo, GLfloat distancia_obj, GLfloat angulo_obj);
//permite reajustar la venta y el reescalado de esta
void changeSize(GLint newWidth, GLint newHeight);