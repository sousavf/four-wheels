#ifndef OBJECTO_H
#define OBJECTO_H

#include <stdlib.h>
#include<GL/glut.h>

struct pos
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class objecto
{
	protected:
		pos posicao;
		GLfloat ang_rot[3];

	public :
		virtual void desenha() = 0;
		virtual void rotacao(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z);
		virtual void translacao(GLfloat x, GLfloat y, GLfloat z);
};

#endif