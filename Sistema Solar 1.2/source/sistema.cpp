#include <Sistema.h>

#include <iostream>
#include <sstream> // string stream
#include <fstream> // File managing

Sistema::Sistema() {
    return;
}

Sistema::Sistema(std::vector<Planeta> &planets) {
    this->add(planets);
}

Sistema::Sistema(std::string file_path) {
    this->cargar_de_archivo(file_path);
}


std::map<const std::string, Planeta> &Sistema::planetas() {
    return this->_planetas;
}


void Sistema::add(Planeta p) {
    // Adds Main Planet to hashmap
    this->_planetas[p.nombre()] = p;

    // Adds name to name list
    this->nombre_planetas.push_back(p.nombre());
}

void Sistema::add(std::vector<Planeta> &planets) {
    for (Planeta p : planets) {
        this->add(p);
    }
}

const std::vector<std::string>& Sistema::showPlanetas() const {
    return this->nombre_planetas;
}

void Sistema::cargar_de_archivo(std::string file_path) {
    std::ifstream file(file_path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not load sistem from file" << std::endl;
        exit(1);
    }

    Planeta planeta;
    Planeta sat;

    std::string name;
    GLfloat     dist;      
    GLfloat     vel_trans; 
    GLfloat     angulo_trans;
    GLfloat     vel_rot;  
    GLfloat     angulo_rot;
    GLfloat     size;         
    GLfloat     red;
    GLfloat     green;
    GLfloat     blue;
    bool        iluminacion;
    int         first_line = 1;
    
    while (std::getline(file, line)) {

        // Permite tratar con la linea como si fuese un stream
        // Y tratar sus valores separados por espacios
        std::stringstream line_stream(line);
        std::string first_token;

        // Carriage Return de windows
        if (first_line) {
            line_stream >> first_token;
            first_line--;
        }

        line_stream >> first_token;

        if (first_token == "#") {
            // This is a satelite
            line_stream >> name;
        }
        else {
            // Planeta
            name = first_token;
        }
        
        line_stream >> dist;
        line_stream >> vel_trans;
        line_stream >> angulo_trans;
        line_stream >> vel_rot;
        line_stream >> angulo_rot;
        line_stream >> size;
        line_stream >> red;
        line_stream >> green;
        line_stream >> blue;
        line_stream >> iluminacion;

        if (first_token == "#") {
            // Satelite
            sat = Planeta(name, dist, vel_trans, angulo_trans, vel_rot, angulo_rot, size, red, green, blue, iluminacion);
            this->add(sat);

            // Cogemos el valor del planeta anterior que seria el 
            // Planeta principal segun el formato del archivo
            this->_planetas[planeta.nombre()].addSatelite(&this->_planetas[name]);
        }
        else {
            // Planeta
            planeta = Planeta(name, dist, vel_trans, angulo_trans, vel_rot, angulo_rot, size, red, green, blue, iluminacion);
            this->add(planeta);

        }        
    }
    file.close();
}


void Sistema::display(GLuint esfera, bool show_orbitas, bool iluminar) {

    if (!iluminar) {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
    }
    else {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
    }

    for (auto& p : this->_planetas) {

        // Si no es un satelite
        if (p.second.mainPlaneta() == NULL) {
            p.second.display(esfera, show_orbitas, iluminar);
        }
    }
}


void Sistema::cargarTexturas() {
    for (auto& p : this->_planetas) {
        p.second.cargaTexturas((".\\resources\\texturas\\" + p.second.nombre() + ".jpg").c_str());
    }
}

void Sistema::move(unsigned int days) {
    

    for (auto& p : this->_planetas) {
        // Si no es un satelite
        if (p.second.mainPlaneta() == NULL) {
            p.second.move(days);

        }
    }
}