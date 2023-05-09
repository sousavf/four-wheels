#ifndef BIDON_H
#define BIDON_H

#include "../carro/objecto.h"
#include "../carro/geraPoligono.h"
#include "../textura.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>

class bidon : public objecto
{
	private:
		GLfloat raioBidon;
		GLfloat alturaRasgoBidon;
		GLfloat alturaPainelBidon;
		GLfloat alturaSector;

		GLint dlBidon;
		
		bool primeiraVez; 

		void desenhaBidon();
		void geraDlBidon();

	public:
		bidon();
		bidon(GLfloat altura, GLfloat raio);

		virtual void desenha();
};

#endif
