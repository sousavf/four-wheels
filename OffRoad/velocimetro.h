#ifndef VELOCIMETRO_
#define VELOCIMETRO_

#include "ODERequirements.h"
#include "ODEHeaders.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "textura.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

using namespace ODE;
using namespace std;

class Velocimetro
{
	private:
		textura Fundo,Limite,Ponteiro;
		void poligono(GLint n, GLfloat x0, GLfloat y0, GLfloat r, GLfloat red, GLfloat green, GLfloat blue);

	public:
		Velocimetro();
		void desenha(const int Speed,int w,int h);
		void init();

};


#endif