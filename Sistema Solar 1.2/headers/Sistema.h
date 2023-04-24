#ifndef SISTEMA_H
#define SISTEMA_H

#include <map>
#include <string>
#include <Planeta.h>
#include <vector>

class Sistema {
private:

    /** <summary>	Hashmap con todos los planetas del sistema y su nombre. </summary> */
    std::map<const std::string, Planeta> _planetas;

    /** <summary>	The nombre planetas. </summary> */
    std::vector<std::string> nombre_planetas;

public:

    /**************************************************************************************************
     * <summary>	Default constructor. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     **************************************************************************************************/
    Sistema();

    /**************************************************************************************************
     * <summary>	Constructor. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <param name="p">	[in,out] A Planeta to process. </param>
     **************************************************************************************************/
    Sistema(std::vector<Planeta> &planets);

    Sistema(std::string file_path);

    void cargar_de_archivo(std::string file_path);

    void display(GLuint esfera,bool flag);

    void move(unsigned int days);

    /**************************************************************************************************
     * <summary>	Gets the planetas. </summary>
     *
     * <remarks>	Pc, 05/04/2023. </remarks>
     *
     * <returns>	A reference to a std::map&lt;const std::string,Planeta&gt; </returns>
     **************************************************************************************************/

    std::map<const std::string, Planeta>& planetas();


    /**************************************************************************************************
     * <summary>	Adds a planeta. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <param name="p">	A Planeta to process. </param>
     **************************************************************************************************/
    void add(Planeta p);

    /**************************************************************************************************
     * <summary>	Adds a vector of planetas. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <param name="planets">	A Planeta to process. </param>
     **************************************************************************************************/
    void add(std::vector<Planeta> &planets);


    /**************************************************************************************************
     * <summary>	Shows a copy of the names of the planetas. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <returns>	A reference to a std::string. </returns>
     **************************************************************************************************/

    const std::vector<std::string>& showPlanetas() const;

    void cargarTexturas();
};


#endif
