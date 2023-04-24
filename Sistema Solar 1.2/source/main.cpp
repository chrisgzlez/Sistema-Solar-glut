
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


#define INIT_WIDHT 1200
#define INIT_HEIGHT 700
#define MOVE_INTERVAL 1 //miliseconds
#define WIN_POS_X 500
#define WIN_POS_Y 100


GLfloat fAngulo, fAngulo2;
GLuint index_esfera;
bool showOrbitas= TRUE;

// Variables globales del menu
int camara_option = 1;
int camara_option_prev = 1;
std::vector<std::string> opciones_menu;

//Variables de iluminacion
GLfloat Ambient[] = { 0.0f, 0.0f,0.0f,1.0f };//no queremos que sea de ambiente

//para que la luz sea brillante difusa y especular
GLfloat Diffuse[] = { 1.0f, 1.0f,1.0f,1.0f };
GLfloat SpecRef[] = { 1.0f, 1.0f,1.0f,1.0f };
GLfloat Specular[] = { 1.0f, 1.0f,1.0f,1.0f };

//Variables de definición de la posicion del foco y direccion de iluminacion
GLfloat LuzPos[] = { 0.0f,0.0f,0.0f,1.0f }; //colocamos la luz en el centro que es donde se encuentra el sol
GLfloat SpotDir[] = { 1.0f,1.0f,1.0f }; //direccion

//Sistema sis;
Sistema sis = Sistema(".\\resources\\datos_planetas.txt");

unsigned int days = 0;
void timer(int a) {
    days++;
    glutTimerFunc(2, timer, 0);
}


void idle() {
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
    if (opcion != 2 && opcion != 3) {
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
    
    int index = 1;

    //añadimos las entradas
    glutAddMenuEntry("Voyayer", index++);
    opciones_menu.push_back("Voyayer");


    glutAddMenuEntry("Toggle Orbitas", index++);
    opciones_menu.push_back("Toggle Orbitas");
    
    glutAddMenuEntry("Toggle Sol", index++);
    opciones_menu.push_back("Toggle Sol");


    // Crear las entradas de forma dinamica
    for (std::string nombre_planeta : sis.showPlanetas()) {
        if (nombre_planeta != "tierra") {
            glutAddMenuEntry(nombre_planeta.c_str(), index++);
            opciones_menu.push_back(nombre_planeta);
        }
    }

    //configuramos el boton que permite realizar esto al click derecho
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Función de dibujo
void display(void) {


	// Limpia los buffer de color y profundidad

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // TODO: -Satelites de planeta convertir a map en vez de vector.
    
    if (opciones_menu[camara_option] == "Voyayer") {
        Camara();

    } else if(opciones_menu[camara_option] == "Toggle Orbitas") {

        if (showOrbitas == TRUE) {
            showOrbitas = FALSE;
        }else {
            showOrbitas = TRUE;
        }

        camara_option = camara_option_prev;

    } else if (opciones_menu[camara_option] == "Toggle Sol") {

        sis.planetas()["sol"].toggle_ilumination();

        camara_option = camara_option_prev;

    } else {

        std::string nombreplaneta = opciones_menu[camara_option];
        Planeta p = (sis).planetas()[nombreplaneta];

        if (p.mainPlaneta() != NULL)
        {
            // Si es Un Satelite
            telescopio(p, *p.mainPlaneta());
        }
        else telescopio(sis.planetas()["tierra"], p);
    }
    
   
    glMatrixMode(GL_MODELVIEW);
	

    // Cargamos la matriz identidad
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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


	// Inicializa las GLUT
	glutInit(&argc, argv);

	// Inicializa el modo de la pantalla RGB y doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	
	// Fija el tamaño de la ventana
	glutInitWindowSize(INIT_WIDHT, INIT_HEIGHT);
	
	// Fija la posición de la ventana
	glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
	
	// Permite poner nombre a la ventana en la barra de título.
	glutCreateWindow("Sistema Solar 1.2");

    //luces
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // Habilita la ocultacion de caras
    glEnable(GL_NORMALIZE);

    //definimos las iluminaciones
   
    glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, LuzPos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, SpotDir);

    //Efectos de foco
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 179.0f); //179 porque 180 da problemas

    //Activamos las luces
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    //Definimos el seguimiento del color como propiedad luminosa de los materiales
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //definimos las propiedades del brillo metalico
    glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
    glMateriali(GL_FRONT, GL_SHININESS, 1);

    index_esfera = esferaText();

    glutSpecialFunc(teclasEspeciales);
	glutDisplayFunc(display);// Define las funciones de Callback  
	glutIdleFunc(idle);
    timer(0);

   

    // Cosas
    glutReshapeFunc(changeSize);
    
    menu();

    //  Activa el test de profundidad y oculta caras internas.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //	Activa las texturas y el modelo de sombreado suavizado.
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);



	glutMainLoop(); // Inicia el lazo de visualización.
	return 0;
}