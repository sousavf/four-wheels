#ifndef GERA_POLIGONO_H
#define GERA_POLIGONO_H

#include <stdlib.h>
#include<GL/glut.h>
class geraPoligono
{
	public:
		
		static void disk();
		static void cilindroFechado(GLdouble loops ,GLdouble outterRadius, GLdouble height, GLdouble slices, GLdouble stacks);
		static void cilindroAberto(GLdouble loops ,GLdouble innerRadius, GLdouble outterRadius, GLdouble height, GLdouble slices, GLdouble stacks);
		static void esfera(GLfloat radius, GLfloat slices, GLfloat stacks);
		static void triangulo(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3);
		static void triangulo(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat nx, GLfloat ny, GLfloat nz);
		static void cubo(GLfloat largura, GLfloat comprimento, GLfloat altura);
};

#endif