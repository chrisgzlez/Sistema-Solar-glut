
/*****************************************************
Autores: Ivan Quintáns González y Cristian Novoa Gonzalez
Practica 4 Sistema Solar 1.2
*************************************************************/


#include <windows.h>		// Inclusión de variables de Windows
#include "glut.h"			// Inclusión de librerías GLUT 
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliare
#include "esfera.h"
#include "sistema.h"



#include <iostream>

//Tamaño de ventana 
int w = 500;
int h = 500;

GLfloat fAngulo, fAngulo2;

//declaracion de los Planetas de nuestro sistema solar


//{distancia,vel_trans,ang_rot,vel_rot,ang_rot,tam
	//listarender,color1,color2,colro3}

Planeta sol = { 0,0,0,10,0,100,0,1,1,0 };
Planeta mercurio = { 200,5.3,0,50,0,50,0,1,0,0 };
Planeta venus = { 350,8,0,30,0,50,0,0,1,0 };
Planeta luna = { 100,9,0,10,0,20,0,1,0,0 };
Planeta tierra = { 600,5,0,10,0,80,0,0,0,1 };
Planeta jupiter = { 900,6,0,60,0,60,0,0,0,1 };
Planeta marte = { 800,2,0,10,0,30,0,0,0,1 };
Planeta saturno = { 1100,4,0,20,0,50,0,1,0,0 };
Planeta urano = { 1250,3,0,40,0,30,0,0,1,0 };
Planeta neptuno = { 1350,4.5,0,10,0,50,0,0,0,1 };

Planeta sol_prueba = { 0., 0., 0., 0.03, 0., 0.25, 0, 1, 0.78, 0.2 };
Planeta p1 = { 0.5, 0.03, 0., 0.03, 0., 0.08, 0, 1.f, 0., 0. };
Planeta p2 = { 0.7, 0.02, 0., 0.02, 0., 0.06, 0, 0., 1.f, 0. };
Planeta p3 = { 0.9, 0.01, 0., 0.01, 0., 0.03, 0, 0., 0., 1.f };


Planeta planetas[] = { sol_prueba, p1, p2, p3 };
int n_planetas = sizeof(planetas) / sizeof(Planeta);


int index_esfera;

void idle() {
    glutPostRedisplay();
}

//funcion que dibuja los ejes
void myEjes() {

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.75f, 0.0f, 0.0f);
    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.75f, 0.0f);
    glEnd();


    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0, 100.75f);
    glEnd();

    //Diagonal
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(75.35f, 75.35, 75.35f);
    glEnd();
}


void translation(Planeta *p) {
	p->angulo_trans += p->vel_trans;
	if (p->angulo_trans > 360)
		p->angulo_trans -= 360.0f;
}

void rotation(Planeta* p) {
    p->angulo_rot += p->vel_rot;
    if (p->angulo_rot > 360)
        p->angulo_rot -= 360.0f;
}

void display_planeta(Planeta p) {

    // Cargamos la matriz identidad
    glLoadIdentity();

    // Pusheamos la matrix identidad al stack
    glPushMatrix(); 

    
        // todos los planetas rotan en el mismo plano con respecto al sol
        
        // Rotacion de translacion
        // con respecto al eje y en la posicion actual (origen)
        glRotatef(p.angulo_trans, 0.0, 1.0, 0.0);
        //glRotatef(0., 0.0, 1.0, 0.0);

        // Transalcion a la posicion del planeta
        // permite que el valor anterior genere transalacion
        glTranslatef(p.dist, 0.0, 0.0);
        //glTranslatef(0, 0.0, 0.0);

        // Realizamos una copia de esta matriz y la pusheamos al stack 
        // Se convierte en la matriz base y su posicion en el origen
        glPushMatrix();
            // Angulo de rotacion sobre si misma
            // TODO: No todos los planetas giran sobre su eje y
            glRotatef(p.angulo_rot, 0.0, 1.0, 0.0);

            //añadimos los ejes al planeta
            myEjes();

            // Tamanho del planeta
            // Al ser una esfera la escalamos de forma proporcional
            glScalef(p.size, p.size, p.size);

            // Color del planeta en rgb
            glColor3f(p.red, p.green, p.blue);

            // Crea la esfera
            // Ejecuta la lista de comandos necesarios para crear
            // una esfera
            glCallList(index_esfera);

        // Quitamos las matrices del stack para dejarlo limpio
        // Y no afectar a futuras operaciones
        glPopMatrix();
    glPopMatrix();

    // HACK: para crear los satélitos, no hacer el pop de la primera matriz
    // De esa forma puedes posicionar los satelites con respecto al planeta
}


// Función de dibujo
void display(void) {
	// Limpia los buffer de color y profundidad
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < n_planetas; i++) {
        display_planeta(planetas[i]);
        translation(&planetas[i]);
        rotation(&planetas[i]);
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

	index_esfera = esfera();

	glutDisplayFunc(display);// Define las funciones de Callback  
	glutIdleFunc(idle);
    glutReshapeFunc(changeSize);

  
	glutMainLoop(); // Inicia el lazo de visualización.
	return 0;
}