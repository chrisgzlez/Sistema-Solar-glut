
/*****************************************************
Autores: Ivan Quintáns González y Cristian Novoa Gonzalez
Practica 4 Sistema Solar 1.2
*************************************************************/

#include <stdlib.h>         // Necesaria en todos para evitar conflicto con glut
                            // Vease: https://stackoverflow.com/questions/14402/glut-exit-redefinition-error

#include <windows.h>		// Inclusión de variables de Windows
#include "glut.h"			// Inclusión de librerías GLUT 
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliare
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
bool showOrbitas= TRUE;

// Variables globales del menu
int camara_option = 1;
int camara_option_prev = 1;
std::vector<std::string> opciones_menu;


//declaracion de los Planetas de nuestro sistema solar


//{distancia,vel_trans,ang_rot,vel_rot,ang_rot,tam
	//listarender,color1,color2,colro3}
//TODO: apañar lo del indice de la esfera

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

Planeta sol_prueba = Planeta    ( "sol prueba", 0., 0., 0., 0.03, 0., 0.25, 1, 0.78, 0.2 );
Planeta p1 = Planeta            ( "p1", 1.5, 0.03, 0., 0.03, 0., 0.08, 1.f, 0., 0. );
Planeta p2 = Planeta            ( "p2", 1.7, 0.02, 0., 0.15, 0., 0.06, 0., 1.f, 0. );
Planeta p3 = Planeta            ( "p3", 1.3, 0.015, 0., 0.1, 0., 0.03, 0., 0., 1.f );
Sistema sis = Sistema(".\\resources\\datos_planetas.txt");

unsigned int days = 0;
void timer() {
    days++;
}


void idle() {
    timer();
    glutPostRedisplay();
}


/*
 * Caso camara, manejar
 * Caso de planetas: le pasamos el nombre y hacemos sis.planetas()[nombre_planeta]
 *      Y obtenemos los datos de ese planeta
*/

void onMenu(int opcion) {
    // TODO cambiar esto
    //en funcion del valor de la camara hacemos el telescopio correspondiente.
    camara_option = opcion;
    if (opcion != 2) {
        camara_option_prev = camara_option;
    }
    glutPostRedisplay();
}

// TODO:
// Vector opciones
// HAcer el vector opciones global extern
// La camara tambien 
// Con extern algo

void menu(void) {
    int menuFondo;

    //creamos el menu
    menuFondo = glutCreateMenu(onMenu);

    opciones_menu.push_back("Nada"); // Para comenzar en la posicion 1

    //añadimos las entradas
    glutAddMenuEntry("Voyayer", 1);
    opciones_menu.push_back("Voyayer");
    glutAddMenuEntry("Toggle Orbitas", 2);
    opciones_menu.push_back("Toggle Orbitas");

    int index = 3;

    // Crear las entradas de forma dinamica
    for (std::string nombre_planeta : sis.showPlanetas()) {
        glutAddMenuEntry(nombre_planeta.c_str(), index++);
        opciones_menu.push_back(nombre_planeta);
    }

    //configuramos el boton que permite realizar esto al click derecho
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Función de dibujo
void display(void) {


	// Limpia los buffer de color y profundidad

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // TODO: -Satelites de planeta convertir a map en vez de vector.
    
    if (opciones_menu[camara_option] == "Voyayer")
    {
        Camara();

    }else if(opciones_menu[camara_option] == "Toggle Orbitas") {

        if (showOrbitas == TRUE) {
            showOrbitas = FALSE;
        }else {
            showOrbitas = TRUE;
        }

        camara_option = camara_option_prev;

    } else
    {
        std::string nombreplaneta = opciones_menu[camara_option];
        Planeta* p = (sis).planetas()[nombreplaneta];

        if ((*p).mainPlaneta() != NULL)
        {
            // Si es Un Satelite
            telescopio(p, (*p).mainPlaneta());
        }
        else telescopio(sis.planetas()["sol prueba"], p);
    }
    
   
    glMatrixMode(GL_MODELVIEW);
	

    // Cargamos la matriz identidad
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    sis.display(index_esfera,showOrbitas);
    sis.move(days);

    glFlush();// Intercambia los buffers gráficos disponibles
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

	// Inicializa las GLUT
	glutInit(&argc, argv);

	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	// Fija el tamaño de la ventana
	glutInitWindowSize(INIT_WIDHT, INIT_HEIGHT);
	
	// Fija la posición de la ventana
	glutInitWindowPosition(1300, 100);
	
	// Permite poner nombre a la ventana en la barra de título.
	glutCreateWindow("Sistema Solar 1.2");


	// Inicializa la visualización
	openGlInit();
    index_esfera = esfera();

    glutSpecialFunc(teclasEspeciales);
	glutDisplayFunc(display);// Define las funciones de Callback  
	glutIdleFunc(idle);

    // Cosas
    glutReshapeFunc(changeSize);
    
    menu();

	glutMainLoop(); // Inicia el lazo de visualización.
	return 0;
}