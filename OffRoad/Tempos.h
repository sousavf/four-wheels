#ifndef TEMPOS_H
#define TEMPOS_H

#include "LapCounter.h"
#include <GL/glut.h>
#include "glf/glf.h"

class Tempos
{
	public:
		Tempos();
		~Tempos();
		void desenha(const LapCounter &counter, int w, int h);
};


#endif