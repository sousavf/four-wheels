#include "caixa.h"

#pragma warning(disable: 4996)

caixa::caixa()
{
	initDefaults();
	
	largura = 5.0f;
	profundidade = 2.0f;
	altura = 2.0f;
	
	pathTexturas = "texturas/obstaculos/caixa/";
	
	flagTexturas = true;
	
	loadTextures();
}

caixa::caixa(string texPath)
{
	initDefaults();

	largura = 5.0f;
	profundidade = 2.0f;
	altura = 2.0f;

	pathTexturas = texPath;
	
	flagTexturas = true;
	
	loadTextures();
}

caixa::caixa(string texPath, GLfloat largura, GLfloat altura, GLfloat profundidade)
{
	initDefaults();
	this->largura = largura;
	this->profundidade = profundidade;
	this->altura = altura;
	pathTexturas = texPath;
	flagTexturas = true;
	loadTextures();
}


void caixa::switchTexturasOnOff()
{
	if(flagTexturas)
		flagTexturas = false;
	else
		flagTexturas = true;
}

void caixa::initDefaults()
{
	posicao.x = 0.0f;
	posicao.y = 0.0f;
	posicao.z = 0.0f;
	ang_rot[0] = 0.0f;
	ang_rot[1] = 0.0f;
	ang_rot[2] = 0.0f;
	texNames[0] = "frente.bmp";
	texNames[1] = "lado.bmp";
}

void caixa::desenha()
{
	//glColor3f(0.5f,0.5f,0.0f);
	//glPushMatrix();
	//	glTranslatef(posicao.x, posicao.y, posicao.z);
	//	glRotatef(ang_rot[0], 1.0f, 0.0f, 0.0f);
	//	glRotatef(ang_rot[1], 0.0f, 1.0f, 0.0f);
	//	glRotatef(ang_rot[2], 0.0f, 0.0f, 1.0f);
	//	glPushMatrix();
	//	glTranslatef(0.0f, 0.0f, altura);
	//	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//		glPushMatrix();
	//			if(flagTexturas)
	//			{
	//				glEnable(GL_TEXTURE_2D);
	//				texturas[0].SetActive();
	//			}
	//			glBegin(GL_QUADS);
	//				glTexCoord2f(0.0,0.0);
	//				glVertex3f(0.0f, 0.0f, 0.0f);
	//				glTexCoord2f(0.0,1.0);
	//				glVertex3f(profundidade, 0.0f, 0.0f);
	//				glTexCoord2f(1.0,1.0);
	//				glVertex3f(profundidade, altura, 0.0f);
	//				glTexCoord2f(1.0,0.0);
	//				glVertex3f(0.0f, altura, 0.0f);
	//			glEnd();
	//			if(flagTexturas)
	//			{
	//				glDisable(GL_TEXTURE_2D);
	//			}
	//			//glRectf(0.0f, 0.0f, profundidade, altura);
	//			glTranslatef(0.0f,0.0f, -largura);
	//			if(flagTexturas)
	//			{
	//				glEnable(GL_TEXTURE_2D);
	//				texturas[0].SetActive();
	//			}
	//			glBegin(GL_QUADS);
	//				glTexCoord2f(0.0,0.0);
	//				glVertex3f(0.0f, 0.0f, 0.0f);
	//				glTexCoord2f(0.0,1.0);
	//				glVertex3f(profundidade, 0.0f, 0.0f);
	//				glTexCoord2f(1.0,1.0);
	//				glVertex3f(profundidade, altura, 0.0f);
	//				glTexCoord2f(1.0,0.0);
	//				glVertex3f(0.0f, altura, 0.0f);
	//			glEnd();
	//			if(flagTexturas)
	//			{
	//				glDisable(GL_TEXTURE_2D);
	//			}
	//			//glRectf(0.0f, 0.0f, profundidade, altura);
	//		glPopMatrix();
	//		glPushMatrix();
	//			glTranslatef(0.0f,0.0f, -largura);
	//			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//			glPushMatrix();
	//				glPushMatrix();
	//					glTranslatef(0.0f, 0.0f, -altura);
	//					if(flagTexturas)
	//					{
	//						glEnable(GL_TEXTURE_2D);
	//						texturas[0].SetActive();
	//					}
	//					glBegin(GL_QUADS);
	//						glTexCoord2f(0.0,0.0);
	//						glVertex3f(0.0f, 0.0f, 0.0f);
	//						glTexCoord2f(0.0,1.0);
	//						glVertex3f(profundidade, 0.0f, 0.0f);
	//						glTexCoord2f(1.0,1.0);
	//						glVertex3f(profundidade, largura, 0.0f);
	//						glTexCoord2f(1.0,0.0);
	//						glVertex3f(0.0f, largura, 0.0f);
	//					glEnd();
	//					if(flagTexturas)
	//					{
	//						glDisable(GL_TEXTURE_2D);
	//					}
	//					//glRectf(0.0f,0.0f,profundidade, largura);
	//				glPopMatrix();
	//				glPushMatrix();
	//					if(flagTexturas)
	//					{
	//						glEnable(GL_TEXTURE_2D);
	//						texturas[0].SetActive();
	//					}
	//					glBegin(GL_QUADS);
	//						glTexCoord2f(0.0,0.0);
	//						glVertex3f(0.0f, 0.0f, 0.0f);
	//						glTexCoord2f(0.0,1.0);
	//						glVertex3f(profundidade, 0.0f, 0.0f);
	//						glTexCoord2f(1.0,1.0);
	//						glVertex3f(profundidade, largura, 0.0f);
	//						glTexCoord2f(1.0,0.0);
	//						glVertex3f(0.0f, largura, 0.0f);
	//					glEnd();
	//					if(flagTexturas)
	//					{
	//						glDisable(GL_TEXTURE_2D);
	//					}
	//					//glRectf(0.0f,0.0f,profundidade, largura);
	//				glPopMatrix();
	//			glPopMatrix();
	//		glPopMatrix();
	//		glPushMatrix();
	//			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	//			if(flagTexturas)
	//			{
	//				glEnable(GL_TEXTURE_2D);
	//				texturas[1].SetActive();
	//			}
	//			glBegin(GL_QUADS);
	//				glTexCoord2f(0.0,0.0);
	//				glVertex3f(0.0f, 0.0f, 0.0f);
	//				glTexCoord2f(0.0,1.0);
	//				glVertex3f(largura, 0.0f, 0.0f);
	//				glTexCoord2f(1.0,1.0);
	//				glVertex3f(largura, altura, 0.0f);
	//				glTexCoord2f(1.0,0.0);
	//				glVertex3f(0.0f, altura, 0.0f);
	//			glEnd();
	//			if(flagTexturas)
	//			{
	//				glDisable(GL_TEXTURE_2D);
	//			}
	//			//glRectf(0.0f,0.0f,largura, altura);
	//			glTranslatef(0.0f, 0.0f, profundidade);
	//			if(flagTexturas)
	//			{
	//				glEnable(GL_TEXTURE_2D);
	//				texturas[1].SetActive();
	//			}
	//			glBegin(GL_QUADS);
	//				glTexCoord2f(0.0,0.0);
	//				glVertex3f(0.0f, 0.0f, 0.0f);
	//				glTexCoord2f(0.0,1.0);
	//				glVertex3f(largura, 0.0f, 0.0f);
	//				glTexCoord2f(1.0,1.0);
	//				glVertex3f(largura, altura, 0.0f);
	//				glTexCoord2f(1.0,0.0);
	//				glVertex3f(0.0f, altura, 0.0f);
	//			glEnd();
	//			if(flagTexturas)
	//			{
	//				glDisable(GL_TEXTURE_2D);
	//			}
	//			//glRectf(0.0f,0.0f,largura, altura);
	//		glPopMatrix();
	//	glPopMatrix();
	//glPopMatrix();
	glColor3f(0.5f,0.5f,0.0f);
	glPushMatrix();
		glTranslatef(posicao.x, posicao.y, posicao.z);
		glRotatef(ang_rot[0], 1.0f, 0.0f, 0.0f);
		glRotatef(ang_rot[1], 0.0f, 1.0f, 0.0f);
		glRotatef(ang_rot[2], 0.0f, 0.0f, 1.0f);
		glPushMatrix();
			//glTranslatef(0.0, 3.0, 0.0);
			glEnable(GL_TEXTURE_2D);
			texturas[0].SetActive();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(-largura * 0.5f, -altura * 0.5f, profundidade * 0.5f);
				glTexCoord2f(0.0,1.0);
				glVertex3f( largura * 0.5f, -altura * 0.5f, profundidade * 0.5f);
				glTexCoord2f(1.0,1.0);
				glVertex3f( largura * 0.5f,  altura * 0.5f, profundidade * 0.5f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(-largura * 0.5f,  altura * 0.5f, profundidade * 0.5f);
			glEnd();
			texturas[0].SetActive();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(-largura * 0.5f, -altura * 0.5f, -profundidade * 0.5f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(-largura * 0.5f,  altura * 0.5f, -profundidade * 0.5f);
				glTexCoord2f(1.0,1.0);
				glVertex3f( largura * 0.5f,  altura * 0.5f, -profundidade * 0.5f);
				glTexCoord2f(1.0,0.0);
				glVertex3f( largura * 0.5f, -altura * 0.5f, -profundidade * 0.5f);
			glEnd();	
			//texturas[0].SetActive();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(-largura * 0.5f, altura * 0.5f,  profundidade * 0.5f);
				glTexCoord2f(0.0,1.0);
				glVertex3f( largura * 0.5f, altura * 0.5f,  profundidade * 0.5f);
				glTexCoord2f(1.0,1.0);
				glVertex3f( largura * 0.5f, altura * 0.5f, -profundidade * 0.5f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(-largura * 0.5f, altura * 0.5f, -profundidade * 0.5f);
			glEnd();
			texturas[0].SetActive();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, -1.0f, 0.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f( largura * 0.5f, -altura * 0.5f, -profundidade * 0.5f);
				glTexCoord2f(0.0,1.0);
				glVertex3f( largura * 0.5f, -altura * 0.5f,  profundidade * 0.5f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(-largura * 0.5f, -altura * 0.5f,  profundidade * 0.5f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(-largura * 0.5f, -altura * 0.5f, -profundidade * 0.5f);
			glEnd();
			texturas[1].SetActive();
			glBegin(GL_QUADS);
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(-largura * 0.5f, -altura * 0.5f, -profundidade * 0.5f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(-largura * 0.5f, -altura * 0.5f,  profundidade * 0.5f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(-largura * 0.5f,  altura * 0.5f,  profundidade * 0.5f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(-largura * 0.5f,  altura * 0.5f, -profundidade * 0.5f);
			glEnd();
			texturas[1].SetActive();
			glBegin(GL_QUADS);
				glNormal3f( 1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f( largura * 0.5f, -altura * 0.5f, -profundidade * 0.5f);
				glTexCoord2f(0.0,1.0);
				glVertex3f( largura * 0.5f, altura * 0.5f,  -profundidade * 0.5f);
				glTexCoord2f(1.0,1.0);
				glVertex3f( largura * 0.5f,  altura * 0.5f,  profundidade * 0.5f);
				glTexCoord2f(1.0,0.0);
				glVertex3f( largura * 0.5f,  -altura * 0.5f, profundidade * 0.5f);
			glEnd();			
		glPopMatrix();
	glPopMatrix();
}

void caixa::loadTextures()
{
	char buffer[256];
	string temp;

	for(int i=0; i<2;i++)
	{
		temp = pathTexturas + texNames[i];
		strncpy(buffer, temp.c_str(), 255);
		texturas[i].LoadTextures(buffer);
	}
}