#ifndef NrVoltas_
#define NrVoltas_

#include "ODERequirements.h"
#include "ODEHeaders.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "glf/glf.h"
#include "textura.h"
#include <string>

using namespace ODE;
using namespace std;

class NrVoltas
{
	private:
		

	public:
		NrVoltas();
		void desenha(int VoltaActual, int VoltasTotal, int w, int h);
		void init();

};


#endif