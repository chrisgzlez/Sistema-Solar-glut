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

    std::map<const std::string, Planeta>& planetas();

    /**************************************************************************************************
     * <summary>	Adds a planeta. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <param name="p">	A Planeta to process. </param>
     **************************************************************************************************/
    void add(Planeta& p);

    /**************************************************************************************************
     * <summary>	Adds a planeta. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <param name="planets">	A Planeta to process. </param>
     **************************************************************************************************/
    void add(std::vector<Planeta> &planets);


    /**************************************************************************************************
     * <summary>	Shows the planetas. </summary>
     *
     * <remarks>	Pc, 04/04/2023. </remarks>
     *
     * <returns>	A reference to a std::string. </returns>
     **************************************************************************************************/

    const std::vector<std::string>& showPlanetas() const;
};


#endif