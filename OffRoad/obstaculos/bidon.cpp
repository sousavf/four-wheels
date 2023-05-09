#include "bidon.h"

bidon::bidon()
{
	ang_rot[0] = 0.0f;
	ang_rot[1] = 0.0f;
	ang_rot[2] = 0.0f;
	posicao.x = 0.0f;
	posicao.y = 0.0f;
	posicao.z = 0.0f;
	raioBidon = 1.0f;
	alturaRasgoBidon = 0.2f;
	alturaPainelBidon = 0.8f;
	alturaSector = alturaRasgoBidon + alturaPainelBidon;
	this->primeiraVez = true;
	 
}

bidon::bidon(GLfloat altura, GLfloat raio)
{
	ang_rot[0] = ang_rot[1] = ang_rot[2] = 0.0f;
	posicao.x = posicao.y = posicao.z = 0.0f;
	this->raioBidon = raio;
	this->alturaRasgoBidon = (0.2f * altura) / 4.0f;
	this->alturaPainelBidon = (0.8f * altura) / 3.0f;
	this->alturaSector = this->alturaRasgoBidon + this->alturaPainelBidon;
	this->primeiraVez = true;
}

void bidon::desenha()
{
	if(this->primeiraVez)
	{
		//this->geraDlBidon();
		this->primeiraVez = false;
	}
	glPushMatrix();
		glTranslatef(posicao.x, posicao.y, posicao.z);
		glRotatef(-ang_rot[0], 1.0f, 0.0f, 0.0f);
		glRotatef(ang_rot[1], 0.0f, 1.0f, 0.0f);
		glRotatef(ang_rot[2], 0.0f, 0.0f, 1.0f);
		//glCallList(this->dlBidon);
		this->desenhaBidon();
	glPopMatrix();
}

void bidon::geraDlBidon()
{
	// Create o id para a lista
	this->dlBidon = glGenLists(1);
	
	// inicializa a lista
	glNewList(this->dlBidon, GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		desenhaBidon();
	// termina a lista
	glEndList();
}

void bidon::desenhaBidon()
{
	GLfloat mat_amb_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_amb_diff_temp[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_shininess_temp[] = { 100.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff_temp);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_temp);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -(this->alturaRasgoBidon * 2.0f + this->alturaPainelBidon * 1.5f));
		glPushMatrix();
			glColor3f(0.1f, 0.1f, 0.1f);
			glPushMatrix();
				geraPoligono::cilindroFechado(1.0f, raioBidon * 1.05f, alturaRasgoBidon, 10.0f, 1.0f);	
			glPopMatrix();
			glColor3f(0.3f, 0.3f, 0.3f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, alturaRasgoBidon);
				geraPoligono::cilindroFechado(1.0f, raioBidon, alturaPainelBidon, 10.0f, 1.0f);
			glPopMatrix();
			glColor3f(0.1f, 0.1f, 0.1f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, alturaSector);
				geraPoligono::cilindroFechado(1.0f, raioBidon * 1.05f, alturaRasgoBidon, 10.0f, 1.0f);	
			glPopMatrix();
			glColor3f(0.3f, 0.3f, 0.3f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, alturaSector + alturaRasgoBidon);
				geraPoligono::cilindroFechado(1.0f, raioBidon, alturaPainelBidon, 10.0f, 1.0f);
			glPopMatrix();
			glColor3f(0.1f, 0.1f, 0.1f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, alturaSector * 2.0f);
				geraPoligono::cilindroFechado(1.0f, raioBidon * 1.05f, alturaRasgoBidon, 10.0f, 1.0f);	
			glPopMatrix();
			glColor3f(0.3f, 0.3f, 0.3f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, alturaSector * 2.0f + alturaRasgoBidon);
				geraPoligono::cilindroFechado(1.0f, raioBidon, alturaPainelBidon, 10.0f, 1.0f);
			glPopMatrix();
			glColor3f(0.1f, 0.1f, 0.1f);
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, alturaSector * 3.0f);
				geraPoligono::cilindroFechado(1.0f, raioBidon * 1.05f, alturaRasgoBidon, 10.0f, 1.0f);	
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
}