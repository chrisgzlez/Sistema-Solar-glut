#ifndef PLANETA_H
#define PLANETA_H


#define _USE_MATH_DEFINES
#include <cmath>

#include <stdlib.h>         
#include <glut.h>
#include <windows.h>		// Inclusi�n de variables de Windows
#include "glut.h"			// Inclusi�n de librer�as GLUT 
#include <GL/gl.h>			// Inclusi�n de librer�as GL
#include <GL/glu.h>			// Inclusi�n de librer�as auxiliare
#include <vector>
#include <string>


class Planeta;

class Planeta {
protected:
    std::vector<Planeta*> _satelites;    // lista de satelites del planeta

private:

    Planeta* _main_planet = NULL;   // Only applies to subclasses

    std::string _name;
    GLfloat     _dist;           // Distancia al centro
    GLfloat     _vel_trans;      // Velocidad de transalacion
    GLfloat     _vel_rot;        // Velocidad rotacion
    GLfloat     _size;           // Size del planeta
    GLuint      _render;    // lista de comandos para genera TODO algo

    // Telescopio telescopio;

    // colores rgb del planeta
    GLfloat     _red;
    GLfloat     _green;
    GLfloat     _blue;

    void ejes();

public:
    GLfloat     _angulo_trans;   // Angulo de transalacion
    GLfloat     _angulo_rot;     // Angulo de rotacion

    Planeta();


    /**************************************************************************************************
     * <summary>	Constructor. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     *
     * <param name="nombre">	The nombre. </param>
     * <param name="dist">  	Distancia al centro. </param>
     * <param name="vt">		Velocidad de transalacion. </param>
     * <param name="at">		Angulo de transalcion inicial. </param>
     * <param name="vr">		Velocidad de rotacion. </param>
     * <param name="ar">		Angulo de rotacion inicial. </param>
     * <param name="size">  	Tama�o del planeta. </param>
     * <param name="render">	Indice de la lista de renderizado. </param>
     * <param name="r">			Color rojo rgb. </param>
     * <param name="g">			Color verde rgb. </param>
     * <param name="b">			Color azul rgb. </param>
     **************************************************************************************************/

    Planeta(std::string nombre, GLfloat dist, GLfloat vt, GLfloat at, GLfloat vr, GLfloat ar, GLfloat size, GLfloat r, GLfloat g, GLfloat b);

    /**************************************************************************************************
     * <summary>	Devuelve un puntero de solo lectura del planeta principal. </summary>
     *
     * <remarks>	Pc, 05/04/2023. </remarks>
     *
     * <returns>	Null if it fails, else a pointer to a const Planeta. </returns>
     **************************************************************************************************/

    const Planeta* mainPlaneta() const;

    /**************************************************************************************************
     * <summary>
     *  Devuelve un puntero constante (no se puede cambiar su referencia) del planeta principal.
     * </summary>
     *
     * <remarks>	Pc, 05/04/2023. </remarks>
     *
     * <returns>	Null if it fails, else a pointer to a Planeta. </returns>
     **************************************************************************************************/
    Planeta* const mainPlaneta();


    /**************************************************************************************************
     * <summary>	Gets the nombre. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <returns>	A reference to a const std::string. </returns>
     **************************************************************************************************/
    const std::string& nombre() const;

    /**************************************************************************************************
     * <summary>	Gets the distance. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <returns>	A reference to a const GLuint. </returns>
     **************************************************************************************************/

    const GLuint& dist() const;

    /**************************************************************************************************
     * <summary>
     *  Gets a copy of the satelites. You can modify the properties of the satelites but you cant
     *  add/remove them.
     * </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <returns>	A reference to a const std::vector. </returns>
     **************************************************************************************************/

    const std::vector<Planeta*>& satelites() const;

    /**************************************************************************************************
     * <summary>	Adds a satelite. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <param name="sat">	[in,out] A Planeta to process. </param>
     **************************************************************************************************/

    void addSatelite(Planeta* sat);

    /**************************************************************************************************
     * <summary>	Adds a satelite. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <param name="satelites">	The satelites. </param>
     **************************************************************************************************/

    void addSatelite(std::vector<Planeta*> &satelites);

    void move(unsigned int days);

    void showOrbita();

    /**************************************************************************************************
     * <summary>	Realiza el dislay del Planeta y de sus satelites. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     *
     * <param name="esfera">	The esfera. </param>
     **************************************************************************************************/
    void display(GLuint esfera);

    /**************************************************************************************************
     * <summary>	Trasalada el planeta a lo largo de su orbita. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     **************************************************************************************************/
    void translate(unsigned int time);

    /**************************************************************************************************
     * <summary>	Rota el planeta sobre su propio eje. </summary>
     *
     * <remarks>	Pc, 03/04/2023. </remarks>
     **************************************************************************************************/
    void rotate(unsigned int time);
};

#endif
