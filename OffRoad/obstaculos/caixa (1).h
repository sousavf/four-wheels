#ifndef CAIXA_H
#define CAIXA_H

#include "../carro/objecto.h"
#include "../textura.h"
#include <stdlib.h>
#include <string>
#include <GL/glut.h>
#include <GL/glaux.h>

using namespace std;

class caixa : public objecto
{
	private:
		GLfloat largura;
		GLfloat profundidade;
		GLfloat altura;
		
		textura texturas[2];
		string texNames[2];
		string pathTexturas;
		
		bool flagTexturas;

		void loadTextures();

		void initDefaults();

	public:
		caixa();
		caixa(string texPath);
		caixa(string texPath, GLfloat largura, GLfloat comprimento, GLfloat altura);

		virtual void desenha();
		void switchTexturasOnOff();
};

#endif
