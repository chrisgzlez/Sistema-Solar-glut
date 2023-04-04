#include <stdlib.h>         
#include <glut.h>
#include <windows.h>		// Inclusi�n de variables de Windows
#include "glut.h"			// Inclusi�n de librer�as GLUT 
#include <GL/gl.h>			// Inclusi�n de librer�as GL
#include <GL/glu.h>			// Inclusi�n de librer�as auxiliare

/**************************************************************************************************
 * <summary>	Camara del programa . </summary>
 *
 * <remarks>	Ivanq, 4/4/2023. </remarks>
 *
 * <param name="w">	The width. </param>
 * <param name="h">	The height. </param>
 **************************************************************************************************/

void Camara();

/**************************************************************************************************
 * <summary>	Teclas que nos permiten desplazarnos por el sistema solar. </summary>
 *
 * <remarks>	Ivanq, 4/4/2023. </remarks>
 *
 * <param name="cursor">	The cursor. </param>
 * <param name="x">			The x coordinate. </param>
 * <param name="y">			The y coordinate. </param>
 **************************************************************************************************/

void teclasEspeciales(int cursor, int x, int y);

/**************************************************************************************************
 * <summary>	Telescopio (desde la tierra al punto que nosotros queramos). </summary>
 *
 * <remarks>	Ivanq, 4/4/2023. </remarks>
 *
 * <param name="distancia">	   	The distancia. </param>
 * <param name="angulo">	   	The angulo. </param>
 * <param name="distancia_obj">	The distancia object. </param>
 * <param name="angulo_obj">   	The angulo object. </param>
 **************************************************************************************************/

void telescopio(GLfloat distancia, GLfloat angulo, GLfloat distancia_obj, GLfloat angulo_obj);

/**************************************************************************************************
 * <summary>	Change size.Permite reajustar la venta y el reescalado de esta. </summary>
 *
 * <remarks>	Ivanq, 4/4/2023. </remarks>
 *
 * <param name="newWidth"> 	Width of the new. </param>
 * <param name="newHeight">	Height of the new. </param>
 **************************************************************************************************/

void changeSize(GLint newWidth, GLint newHeight);

/**************************************************************************************************
 * <summary>	Permite elegir la camara que queramos en el menu y pasarsela al display. </summary>
 *
 * <remarks>	Ivanq, 4/4/2023. </remarks>
 *
 * <param name="opcion">	The opcion. </param>
 **************************************************************************************************/

void onMenu(int opcion);

/**************************************************************************************************
 * <summary>	Creacion y configuracion del menu. </summary>
 *
 * <remarks>	Ivanq, 4/4/2023. </remarks>
 **************************************************************************************************/

void menu();
