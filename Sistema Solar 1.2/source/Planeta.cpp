#include <planeta.h>
//#include <camara.h>

Planeta::Planeta() {
    return;
}


Planeta::Planeta(std::string nombre, GLfloat dist, GLfloat vt, GLfloat at, GLfloat vr, GLfloat ar, GLfloat s, GLuint render, GLfloat r, GLfloat g, GLfloat b) {
    this->_name = nombre;
    this->_dist = dist;
    this->_vel_trans = vt;
    this->_angulo_trans = at;
    this->_vel_rot = vr;
    this->_angulo_rot = ar;
    this->_size = s;
    this->_render = render;
    this->_red = r;
    this->_green = g;
    this->_blue = b;
}

const std::string& Planeta::nombre() const {
    return this->_name;
}

const std::vector<Planeta>& Planeta::satelites() const {
    return this->_satelites;
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


void Planeta::translate() {
    this->_angulo_trans += this->_vel_trans;
    if (this->_angulo_trans > 360)
        this->_angulo_trans -= 360.0f;
}

void Planeta::rotate() {
    this->_angulo_rot += this->_vel_rot;
    if (this->_angulo_rot > 360)
        this->_angulo_rot -= 360.0f;
}

void Planeta::display(GLuint esfera) {

    // Cargamos la matriz identidad
    glLoadIdentity();

    // Pusheamos la matrix identidad al stack
    glPushMatrix();

        // todos los planetas rotan en el mismo plano con respecto al sol

        // Rotacion de translacion
        // con respecto al eje y en la posicion actual (origen)
        glRotatef(this->_angulo_trans, 0.0, 1.0, 0.0);

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

            // Si tiene satelites le hace el display
            if (!this->_satelites.empty()) {
                for (Planeta sat : this->_satelites) {
                    sat.display(esfera);
                }
            }

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
    glPopMatrix();

    // HACK: para crear los satélitos, no hacer el pop de la primera matriz
    // De esa forma puedes posicionar los satelites con respecto al planeta
}


//fov
float fovy = 45;

void changeSize(GLint newWidth, GLint newHeight) {

    //configuaramos el view port al ancho y alto nuevo
    glViewport(0, 0, newWidth, newHeight);
    
    //cargamos la matriz de proyeccion
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //cambiamos la matriz de proyeccion 
    gluPerspective(fovy, (float)newWidth/(float)newHeight, 1.0, 500);

    //julian no la utiliza ver que hace esta mierda
    glutPostRedisplay();
    
     
}