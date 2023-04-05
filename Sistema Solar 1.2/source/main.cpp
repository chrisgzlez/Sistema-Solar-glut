
/*****************************************************
Autores: Ivan Quint�ns Gonz�lez y Cristian Novoa Gonzalez
Practica 4 Sistema Solar 1.2
*************************************************************/

#include <stdlib.h>         // Necesaria en todos para evitar conflicto con glut
                            // Vease: https://stackoverflow.com/questions/14402/glut-exit-redefinition-error

#include <windows.h>		// Inclusi�n de variables de Windows
#include "glut.h"			// Inclusi�n de librer�as GLUT 
#include <GL/gl.h>			// Inclusi�n de librer�as GL
#include <GL/glu.h>			// Inclusi�n de librer�as auxiliare
#include <esfera.h>
#include <Planeta.h>
#include <Sistema.h>
#include <vision.h>



#include <iostream>

#define INIT_WIDHT 500
#define INIT_HEIGHT 500
#define MOVE_INTERVAL 1 //miliseconds


GLfloat fAngulo, fAngulo2;
GLuint index_esfera;


//declaracion de los Planetas de nuestro sistema solar


//{distancia,vel_trans,ang_rot,vel_rot,ang_rot,tam
	//listarender,color1,color2,colro3}
//TODO: apa�ar lo del indice de la esfera

/*
Planeta sol = Planeta( "sol", 0,0,0,10,0,100, index_esfera,1,1,0 );
Planeta mercurio = Planeta( 200,5.3,0,50,0,50, index_esfera,1,0,0 );
Planeta venus = Planeta( 350,8,0,30,0,50, index_esfera,0,1,0 );
Planeta luna = Planeta( 100,9,0,10,0,20, index_esfera,1,0,0 );
Planeta tierra = Planeta( 600,5,0,10,0,80, index_esfera,0,0,1 );
Planeta jupiter = Planeta( 900,6,0,60,0,60, index_esfera,0,0,1 );
Planeta marte = Planeta( 800,2,0,10,0,30, index_esfera,0,0,1 );
Planeta saturno = Planeta( 1100,4,0,20,0,50, index_esfera,1,0,0 );
Planeta urano = Planeta( 1250,3,0,40,0,30, index_esfera,0,1,0 );
Planeta neptuno = Planeta( 1350,4.5,0,10,0,50, index_esfera,0,0,1 );
*/

Planeta sol_prueba = Planeta( "sol prueba", 0., 0., 0., 0.03, 0., 0.25, index_esfera, 1, 0.78, 0.2 );
Planeta p1 = Planeta( "p1", 0.5, 0.03, 0., 0.03, 0., 0.08, index_esfera, 1.f, 0., 0. );
Planeta p2 = Planeta("p2", 0.7, 0.02, 0., 0.15, 0., 0.06, index_esfera, 0., 1.f, 0. );
Planeta p3 = Planeta("p3", 0.1, -0.15, 0., 0.1, 0., 0.03, index_esfera, 0., 0., 1.f );

Sistema sis;

unsigned int days = 0;
void timer() {
    days++;
}


void idle() {
    timer();
    glutPostRedisplay();
}


// Funci�n de dibujo
void display(void) {


	// Limpia los buffer de color y profundidad

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Camara();

    // switch tipos de camara
    // TODO: -Satelites de planeta convertir a map en vez de vector.
    
    /*
    if (vectoropciones[camara] == "Voyayer") Camara();
    else {
        std::string nombreplaneta = vectoropciones[camara];
        if (satelite) telescopio(sis.planetas()[nombreplaneta], sis.planetas()[nombreplaneta]);
        else telescopio(sis.planetas()["tierra"], sis.planetas()[nombreplaneta]);

    }
    */
   
    glMatrixMode(GL_MODELVIEW);
	

    // Cargamos la matriz identidad
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    sis.display(index_esfera);
    sis.move(days);

    glFlush();// Intercambia los buffers gr�ficos disponibles
	glutSwapBuffers();
}

void openGlInit() {
	//Habilito aqui el depth en vez de arriba para los usuarios de linux y mac mejor arriba
	//Incializaciones varias
	glClearDepth(1.0f); //Valor z-buffer
	glClearColor(.0f, 0.f, 0.f, .0f);  // valor limpieza buffer color (fondo)
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); //ocultacion caras back
	glCullFace(GL_NORMALIZE);
}

int main(int argc, char **argv) {

    p2.addSatelite(&p3);

    std::vector<Planeta*> plts = { &sol_prueba, &p1, &p2, &p3 };
    sis = Sistema(plts);

	// Inicializa las GLUT
	glutInit(&argc, argv);

	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	// Fija el tama�o de la ventana
	glutInitWindowSize(INIT_WIDHT, INIT_HEIGHT);
	
	// Fija la posici�n de la ventana
	glutInitWindowPosition(1300, 100);
	
	// Permite poner nombre a la ventana en la barra de t�tulo.
	glutCreateWindow("Sistema Solar 1.2");


	// Inicializa la visualizaci�n
	openGlInit();
    index_esfera = esfera();

    glutSpecialFunc(teclasEspeciales);
	glutDisplayFunc(display);// Define las funciones de Callback  
	glutIdleFunc(idle);

    // Cosas
    glutReshapeFunc(changeSize);
    
    menu();

	glutMainLoop(); // Inicia el lazo de visualizaci�n.
	return 0;
}