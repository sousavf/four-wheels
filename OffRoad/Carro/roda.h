#ifndef RODA_H
#define RODA_H

#include <stdlib.h>
#include<GL/glut.h>
#include<GL/glaux.h>
#include<math.h>
#include"geraPoligono.h"
#include"objecto.h"
#include"definicoes.h"
#include<iostream>
using namespace std;

class roda : public objecto
{
	private:
		GLfloat raioJante;
		GLfloat larguraJante;
		GLfloat alturaPneu;
		GLfloat larguraPneu;
		GLfloat raioRoda;
		GLfloat diametroRoda;	
		GLfloat corJante[3];
		GLint dlPneu;
		GLint dlJante;
		int contaRenderizacoes;

		void geraDlPneu();
		void geraDlJante();
		void desenhaJante();
		void desenhaPneu();

	public:
		roda();
		roda(GLfloat rotX, GLfloat rotY, GLfloat rotZ, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat raio_jante, GLfloat largura_jante, GLfloat altura_pneu, GLfloat largura_pneu, GLfloat cor_jante[3]);
		
		void setRotacaoY(GLfloat ang_y);
		void setRotacaoZ(GLfloat ang_z);
		
		GLfloat getRotacaoY();
		GLfloat getRotacaoZ();
		GLfloat getLarguraPneu();
		GLfloat getRaioRoda();
		
		void setCor(GLfloat *cJante);

		void initTextures(void);
		virtual void desenha();
};

#endif
