#define _USE_MATH_DEFINES
#include <cmath>

#include <planeta.h>
#include <iostream>

// Es necesario para que el stb_image funcione
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//#include <camara.h>


Planeta::Planeta() {
    return;
}


Planeta::Planeta(std::string nombre, GLfloat dist, GLfloat vt, GLfloat at, GLfloat vr, GLfloat ar, GLfloat s, GLfloat r, GLfloat g, GLfloat b,GLuint textura) {
    this->_name = nombre;
    this->_dist = dist;

    // Translacion
    this->_vel_trans = vt;
    // Guardamos la posicion inicial
    this->_angulo_trans_init = at;
    // Asignamos el angulo inicial al actual
    this->_angulo_trans = this->_angulo_trans_init;

    // Rotacion
    this->_vel_rot = vr;
    // Guardamos la posicion inicial
    this->_angulo_rot_init = ar;
    // Asignamos el angulo inicial al actual
    this->_angulo_rot = this->_angulo_rot_init;

    this->_size = s;
    //this->_render = render;

    // Color
    this->_red = r;
    this->_green = g;
    this->_blue = b;

    //textura 
    this->_textura = textura;
}

const Planeta& Planeta::mainPlaneta() const {
    return *this->_main_planet;
}

Planeta* const Planeta::mainPlaneta() {
    return this->_main_planet;
}


const std::string& Planeta::nombre() const {
    return this->_name;
}

const std::vector<Planeta*>& Planeta::satelites() const {
    return this->_satelites;
}

const GLfloat& Planeta::dist() const {
    return this->_dist;
}


void Planeta::addSatelite(Planeta* sat) {

    // Ponemos este planeta como el planeta principal
    sat->_main_planet = this;

    // Añadimos satelite al vector de satelites
    this->_satelites.push_back(sat);
}

void Planeta::addSatelite(std::vector<Planeta*>& satelites) {
    for (Planeta *sat : satelites) {
        this->addSatelite(sat);
    }
}

void Planeta::Carga_Texturas(char* imagen) {
    // load and create a texture 
    // -------------------------

    glGenTextures(1, &this->_textura);
    glBindTexture(GL_TEXTURE_2D, this->_textura); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load(imagen, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data); //con mimap 

    }
    else
    {
        //std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}


//funcion que dibuja los ejes
void Planeta::ejes() {

    // Eje x
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.5 * this->_size, 0.0f, 0.0f);
    glEnd();

    // Eje y
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.5 * this->_size, 0.0f);
    glEnd();

    // Eje z
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0, 1.5 * this->_size);
    glEnd();

    //Diagonal
    glColor3f(1.0f, 1.0f, 1.0f); // blanco
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.25 * this->_size, 1.25 * this->_size, 1.25 * this->_size);
    glEnd();
}


void Planeta::translate(unsigned int time) {
    this->_angulo_trans = this->_angulo_trans_init + (time * this->_vel_trans);
    if (this->_angulo_trans >= 360)
        this->_angulo_trans -= 360;
}

// TODO : Manejar valores negativos
void Planeta::rotate(unsigned int time) {
    this->_angulo_rot = this->_angulo_rot_init + (time * this->_vel_rot);
    if (this->_angulo_rot > 360)
        this->_angulo_rot -= 360;
}

void Planeta::showOrbita() {
    GLfloat x_pos, z_pos;
    GLfloat step = 2 * M_PI / 360;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i++) {
        x_pos = (GLfloat)cos(i * step);
        z_pos = (GLfloat)sin(i * step);
        glColor3f(1., 1., 1.);
        glVertex3f(this->_dist * x_pos, 0.0, this->_dist * z_pos);
    }
    glEnd();
    glFlush();
}

void Planeta::display(GLuint esfera,bool flag) {

    // Pusheamos la matrix identidad al stack
    glPushMatrix();

    //en el caso del sol hacer disable y ponerlo

    //glDisable(GL_LIGHTING);

        /// Orbita
        if (flag) {
            this->showOrbita();
        }
        /// 
        

        // todos los planetas rotan en el mismo plano con respecto al sol

        // Rotacion de translacion
        // con respecto al eje y en la posicion actual (origen)
        glRotatef(this->_angulo_trans, 0.0, 1.0, 0.0);
        //glRotatef(180.0, 0.0, 1.0, 0.0);

        // Transalcion a la posicion del planeta
        // permite que el valor anterior genere transalacion
        glTranslatef(this->_dist, 0.0, 0.0);

        // Realizamos una copia de esta matriz y la pusheamos al stack 
        // Se convierte en la matriz base y su posicion en el origen
        glPushMatrix();

            // Angulo de rotacion sobre si misma
            // TODO: No todos los planetas giran sobre su eje y
            glRotatef(this->_angulo_rot, 0.0, 1.0, 0.0);

            //añadimos los ejes al planeta
            ejes();

            // Tamanho del planeta
            // Al ser una esfera la escalamos de forma proporcional
            glScalef(this->_size, this->_size, this->_size);

            // Color del planeta en rgb
            glColor3f(this->_red, this->_green, this->_blue);

            // Crea la esfera
            // Ejecuta la lista de comandos necesarios para crear
            // una esfera
            //glCallList(this->render);
            glCallList(esfera);

        // Quitamos las matrices del stack para dejarlo limpio
        // Y no afectar a futuras operaciones
        glPopMatrix();
        glEnable(GL_LIGHTING);

        /// Satelites
        for (Planeta *sat : this->_satelites) {
            (*sat).display(esfera,flag);
        }
        ///

    glPopMatrix();

    // HACK: para crear los satélitos, no hacer el pop de la primera matriz
    // De esa forma puedes posicionar los satelites con respecto al planeta
}

void Planeta::move(unsigned int days) {
    this->translate(days);
    this->rotate(days);

    for (Planeta* sat : this->_satelites) {
        (*sat).move(days);
    }
}


