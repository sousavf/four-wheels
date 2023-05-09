#include "objecto.h"

void objecto::rotacao(GLfloat ang_x, GLfloat ang_y, GLfloat ang_z)
{
	ang_rot[0] = ang_x;
	ang_rot[1] = ang_y;
	ang_rot[2] = ang_z;
}

void objecto::translacao(GLfloat x, GLfloat y, GLfloat z)
{
	posicao.x = x;
	posicao.y = y;
	posicao.z = z;
}