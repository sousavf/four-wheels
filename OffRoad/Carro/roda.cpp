#include "roda.h"

roda::roda()
{
	ang_rot[0] = 0.0f;
	ang_rot[1] = 0.0f;
	ang_rot[2] = 0.0f;
	posicao.x = 0.0f;
	posicao.y = 0.0f;
	posicao.z = 0.0f;
	raioJante = RAIO_JANTE;
	alturaPneu = ALTURA_PNEU;
	larguraJante = LARGURA_JANTE;
	larguraPneu = LARGURA_PNEU;
	raioRoda = alturaPneu + raioJante;
	diametroRoda = raioRoda * 2.0f;
	corJante[0] = 0.0f;
	corJante[1]	= 0.2f;
	corJante[2] = 0.0f;
	contaRenderizacoes = 0;
	dlJante = 0;
	dlPneu = 0;
}

roda::roda(GLfloat rotX, GLfloat rotY, GLfloat rotZ, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat raio_jante, GLfloat largura_jante, GLfloat altura_pneu, GLfloat largura_pneu, GLfloat cor_jante[3])
{
	ang_rot[0] = rotX;
	ang_rot[1] = rotY;
	ang_rot[2] = rotZ;
	posicao.x = posX;
	posicao.y = posY;
	posicao.z = posZ;
	raioJante = raio_jante;
	larguraJante = largura_jante;
	alturaPneu = altura_pneu;
	larguraPneu = largura_pneu;
	raioRoda = alturaPneu + raioJante;
	diametroRoda = raioRoda * 2.0f;
	corJante[0] = cor_jante[0];
	corJante[1] = cor_jante[1];
	corJante[2] = cor_jante[2];
	contaRenderizacoes = 0;
	dlJante = 0;
	dlPneu = 0;
}

void roda::setCor(GLfloat *cJante)
{
	corJante[0] = cJante[0];
	corJante[1]	= cJante[1];
	corJante[2] = cJante[2];
}

void roda::setRotacaoY(GLfloat ang_y)
{
	ang_rot[1] = ang_y;
}

GLfloat roda::getRotacaoY()
{
	return ang_rot[1];
}

void roda::setRotacaoZ(GLfloat ang_z)
{
	ang_rot[2] = ang_z;
}

GLfloat roda::getRotacaoZ()
{
	return ang_rot[2];
}

GLfloat roda::getLarguraPneu()
{
	return larguraPneu;
}

GLfloat roda::getRaioRoda()
{
	return raioRoda;
}

void roda::geraDlJante()
{
	this->dlJante = glGenLists(1);
	
	glNewList(this->dlJante,GL_COMPILE);
		desenhaJante();
	glEndList();
}

void roda::geraDlPneu()
{
	this->dlPneu = glGenLists(1);
	
	glNewList(this->dlPneu,GL_COMPILE);
		desenhaPneu();
	glEndList();
}

void roda::desenha()
{
	/*if(this->contaRenderizacoes == 0)
	{
		this->geraDlPneu();
		this->geraDlJante();
		this->contaRenderizacoes++;
	}
	this->contaRenderizacoes++;*/
	glFlush();
	glPushMatrix();
		//mover a roda para o sitio onde será desenhada
		glTranslatef(posicao.x,posicao.y,posicao.z);
		//aplicar os variados angulos á roda
		glRotatef(ang_rot[0],1.0f,0.0f,0.0f);
		glRotatef(ang_rot[1],0.0f,1.0f,0.0f);
		glRotatef(ang_rot[2],0.0f,0.0f,1.0f);
		glPushMatrix();
			desenhaPneu();
			desenhaJante();
			//glCallList(this->dlPneu);
		glPopMatrix();
	glPopMatrix();
}

void roda::desenhaJante()
{
	GLfloat mat_amb_diff[] = { this->corJante[0], this->corJante[1], this->corJante[2], 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
	GLfloat alturaParafuso = larguraJante / 8.0f;

	glPushMatrix();
	glColor3f(corJante[0], corJante[1], corJante[2]);
	geraPoligono::cilindroFechado(1.0f, raioJante, larguraJante, 30.0f, 1.0f);
	glPushMatrix();
		glColor3f(0.5f,0.5f,0.5f);
		glPushMatrix();
			glTranslatef(0.0f, raioJante / 3.0f, 0.0);
			geraPoligono::cilindroFechado(1.0f, raioJante / 10.0, alturaParafuso, 6.0f, 1.0f);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, -raioJante / 3.0f, 0.0f);
			geraPoligono::cilindroFechado(1.0f, raioJante / 10.0, alturaParafuso, 6.0f, 1.0f);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-raioJante / 3.0f, 0.0f, 0.0f);
			geraPoligono::cilindroFechado(1.0f, raioJante / 10.0, alturaParafuso, 6.0f, 1.0f);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(raioJante / 3.0f, 0.0f, 0.0f);
			geraPoligono::cilindroFechado(1.0f, raioJante / 10.0, alturaParafuso, 6.0f, 1.0f);
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	GLfloat mat_amb_diff2[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff2);

}

void roda::desenhaPneu()
{	
	GLfloat mat_amb_diff[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_shininess_temp[] = { 100.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_temp);
	glPushMatrix();
		glColor3f(0.0f,0.0f,0.0f);
		geraPoligono::cilindroAberto(1.0f, raioJante, raioRoda, larguraPneu, 30.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, -larguraPneu);
		geraPoligono::cilindroAberto(1.0f, raioJante, raioJante, larguraPneu, 30.0f, 1.0f);
	glPopMatrix();
	GLfloat mat_amb_diff2[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff2);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

}

