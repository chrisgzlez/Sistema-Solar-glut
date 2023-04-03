#include <planeta.h>
//#include <camara.h>


Planeta::Planeta(GLfloat dist, GLfloat vt, GLfloat at, GLfloat vr, GLfloat ar, GLfloat s, GLuint list, GLfloat r, GLfloat g, GLfloat b) {
    this->dist = dist;
    this->vel_trans = vt;
    this->angulo_trans = at;
    this->vel_rot = vr;
    this->angulo_rot = ar;
    this->size = s;
    this->listarender = list;
    this->red = r;
    this->green = g;
    this->blue = b;
}

//funcion que dibuja los ejes
void Planeta::ejes() {

    // Eje x
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.5 * this->size, 0.0f, 0.0f);
    glEnd();

    // Eje y
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.5 * this->size, 0.0f);
    glEnd();

    // Eje z
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0, 1.5 * this->size);
    glEnd();

    //Diagonal
    glColor3f(1.0f, 1.0f, 1.0f); // blanco
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.25 * this->size, 1.25 * this->size, 1.25 * this->size);
    glEnd();
}


void Planeta::translate() {
    this->angulo_trans += this->vel_trans;
    if (this->angulo_trans > 360)
        this->angulo_trans -= 360.0f;
}

void Planeta::rotate() {
    this->angulo_rot += this->vel_rot;
    if (this->angulo_rot > 360)
        this->angulo_rot -= 360.0f;
}

void Planeta::display(int esfera) {

    // Cargamos la matriz identidad
    glLoadIdentity();

    // Pusheamos la matrix identidad al stack
    glPushMatrix();


    // todos los planetas rotan en el mismo plano con respecto al sol

    // Rotacion de translacion
    // con respecto al eje y en la posicion actual (origen)
    glRotatef(this->angulo_trans, 0.0, 1.0, 0.0);

    // Transalcion a la posicion del planeta
    // permite que el valor anterior genere transalacion
    glTranslatef(this->dist, 0.0, 0.0);

    // Realizamos una copia de esta matriz y la pusheamos al stack 
    // Se convierte en la matriz base y su posicion en el origen
    glPushMatrix();

    // Angulo de rotacion sobre si misma
    // TODO: No todos los planetas giran sobre su eje y
    glRotatef(this->angulo_rot, 0.0, 1.0, 0.0);

    //añadimos los ejes al planeta
    ejes();

    // Tamanho del planeta
    // Al ser una esfera la escalamos de forma proporcional
    glScalef(this->size, this->size, this->size);

    // Color del planeta en rgb
    glColor3f(this->red, this->green, this->blue);

    // Crea la esfera
    // Ejecuta la lista de comandos necesarios para crear
    // una esfera
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