#ifndef SEGMENTO_
#define SEGMENTO_

#include<stdlib.h>
#include<GL/glut.h>
#include<GL/glaux.h>
#include<math.h>
#include<iostream>
#include "textura.h"

using namespace std;

class Segmento
{
	private:
		GLfloat x,y,z;
		textura Text;
		GLfloat size;
		GLuint DLcall;

	public:
		Segmento();
		Segmento(GLfloat x, GLfloat y, GLfloat z, GLfloat size, char * path);
		~Segmento();
		void Textura(const char * path);
		void SetX(GLfloat val);
		void SetY(GLfloat val);
		void SetZ(GLfloat val);
		void SetDLCall(GLuint val);
		void SetSize(GLfloat size);
		GLfloat GetSize() const;
		void desenha();
};
#endif