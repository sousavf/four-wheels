#ifndef CENARIO_H
#define CENARIO_H

#include "textura.h"
#include "ODEHeaders.h"
#include <stdlib.h>
#include<GL/glut.h>
#include<GL/glaux.h>
#include<math.h>
#include <iostream>
#include<string>
using namespace std;
using namespace ODE;

class cenario
{
	private:
		textura texture;
		GLfloat width;
		GLfloat height;
		GLfloat raio;
		GLfloat nrOfPanels;
		GLfloat angle;
		GLint dlCenario;		
		
		ODETrack * track;

		bool primeiraVez;

		void desenhaPainel(GLfloat, GLfloat);
		void desenhaAux();
		void geraDL();
		void loadTexture();
		

	public:
		cenario();
		cenario(ODETrack * trk);
		~cenario();

		void desenha();
};

#endif