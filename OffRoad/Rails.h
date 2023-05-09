#ifndef RAILS_
#define RAILS_

#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glaux.h>
#include<math.h>
#include<iostream>
#include "textura.h"
#include "Rails.h"

using namespace std;

class Rails
{
	private:
		textura RailText;
		GLfloat AlturaAoChao;
		GLfloat AlturaRail;
		GLfloat GrossuraPilares;
		GLfloat StartPilares;


	public:
		Rails();
		void init();
		void desenha(GLfloat TamanhoBloco,int type);
};
#endif