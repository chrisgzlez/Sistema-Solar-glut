#include <Sistema.h>

Sistema::Sistema() {
    return;
}

Sistema::Sistema(std::vector<Planeta> &planets) {
    this->add(planets);
}


std::map<const std::string, Planeta> &Sistema::planetas() {
    return this->_planetas;
}

void Sistema::add(Planeta &p) {
    // Adds to hashmap
    this->_planetas[p.nombre()] = p;

    this->nombre_planetas.push_back(p.nombre());
    for (Planeta s : p.satelites()) {
        this->nombre_planetas.push_back(s.nombre());
    }
    
}

void Sistema::add(std::vector<Planeta> &planets) {
    for (Planeta p : planets) {
        this->add(p);
    }
}

const std::vector<std::string>& Sistema::showPlanetas() const {
    return this->nombre_planetas;
}