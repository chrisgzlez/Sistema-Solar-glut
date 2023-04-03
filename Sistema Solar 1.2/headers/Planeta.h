#include <stdlib.h>         
#include <glut.h>
#include <windows.h>		// Inclusión de variables de Windows
#include "glut.h"			// Inclusión de librerías GLUT 
#include <GL/gl.h>			// Inclusión de librerías GL
#include <GL/glu.h>			// Inclusión de librerías auxiliare


class Planeta {
private:
    GLfloat     dist;           // Distancia al centro
    GLfloat     vel_trans;      // Velocidad de transalacion
    GLfloat     angulo_trans;   // Angulo de transalacion
    GLfloat     vel_rot;        // Velocidad rotacion
    GLfloat     angulo_rot;     // Angulo de rotacion
    GLfloat     size;           // Size del planeta
    GLuint      listarender;    // lista de comandos para genera TODO algo

    // colores rgb del planeta
    GLfloat     red;
    GLfloat     green;
    GLfloat     blue;

    void ejes();

public:

    /**************************************************************************************************
     * <summary>	Constructor. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     *
     * <param name="dist">	Distancia al centro. </param>
     * <param name="vt">  	Velocidad de transalacion. </param>
     * <param name="at">  	Angulo de transalcion inicial. </param>
     * <param name="vr">  	Velocidad de rotacion. </param>
     * <param name="ar">  	Angulo de rotacion inicial. </param>
     * <param name="size">	Tamaño del planeta. </param>
     * <param name="list">	Indice de la lista de renderizado. </param>
     * <param name="r">   	Color rojo rgb. </param>
     * <param name="g">   	Color verde rgb. </param>
     * <param name="b">   	Color azul rgb. </param>
     **************************************************************************************************/
    Planeta(GLfloat dist, GLfloat vt, GLfloat at, GLfloat vr, GLfloat ar, GLfloat size, GLuint list, GLfloat r, GLfloat g, GLfloat b);

    /**************************************************************************************************
     * <summary>	Realiza el dislay del Planeta y de sus satelites. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     *
     * <param name="esfera">	Indice de la lista de comandos para crear la esfera. </param>
     **************************************************************************************************/
    void display(int esfera);

    /**************************************************************************************************
     * <summary>	Trasalada el planeta a lo largo de su orbita. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     **************************************************************************************************/
    void translate();

    /**************************************************************************************************
     * <summary>	Rota el planeta sobre su propio eje. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     **************************************************************************************************/
    void rotate();
};


#define CR 0.0175
#define MYTIEMPO 41

void myCamara(int w, int h);

void myTeclasespeciales(int cursor, int x, int y);
void myTelescopio(GLfloat distancia, GLfloat angulo, GLfloat distancia_obj, GLfloat angulo_obj);
//permite reajustar la venta y el reescalado de esta
void changeSize(GLint newWidth, GLint newHeight);