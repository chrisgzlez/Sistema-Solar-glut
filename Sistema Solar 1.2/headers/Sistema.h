#include <glut.h>

typedef struct { //declaramos nuestro objeto como una estructura con los siguientes campos
	float distancia; 
	float velocidad_trans;
	float angulo_trans;
	float velocidad_rot;
	float angulo_rot;
	int tamano;
	int listarender;
	float color1;
	float color2;
	float color3;
} objeto;

#define CR 0.0175
#define MYTIEMPO 41

void myCamara(int w, int h);

void myTeclasespeciales(int cursor, int x, int y);
void myEjes();
int myEsfera();
void myTelescopio(float distancia, float angulo, float distancia_obj, float angulo_obj);