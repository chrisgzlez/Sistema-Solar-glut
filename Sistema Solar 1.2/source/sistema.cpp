#include <Sistema.h>

Sistema::Sistema() {
    return;
}

Sistema::Sistema(std::vector<Planeta*> &planets) {
    this->add(planets);
}

std::map<const std::string, Planeta*> &Sistema::planetas() {
    return this->_planetas;
}

void Sistema::add(Planeta *p) {
    // Adds Main Planet to hashmap
    this->_planetas[(*p).nombre()] = p;

    // Adds name to name list
    this->nombre_planetas.push_back((*p).nombre());

    // Adds satelites to hashmap and to name list
    for (Planeta* s : (*p).satelites()) {
        this->_planetas[(*s).nombre()] = s;
        this->nombre_planetas.push_back((*s).nombre());
    }
    
}

void Sistema::add(std::vector<Planeta*> &planets) {
    for (Planeta *p : planets) {
        this->add(p);
    }
}

const std::vector<std::string>& Sistema::showPlanetas() const {
    return this->nombre_planetas;
}


void Sistema::display(GLuint esfera) {
    for (auto& p : this->_planetas) {

        // Si no es un satelite
        if ((*p.second).mainPlaneta() == NULL) {
            (*p.second).display(esfera);
        }
    }
}

void Sistema::move(unsigned int days) {
    for (auto& p : this->_planetas) {
        // Si no es un satelite
        if ((*p.second).mainPlaneta() == NULL) {
            (*p.second).move(days);

        }
    }
}