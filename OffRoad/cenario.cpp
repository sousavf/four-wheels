#include "cenario.h"

cenario::cenario()
{
	this->width = 80.0f;
	this->height = 100.0;
	this->nrOfPanels = 8;

	this->raio = this->width;
	
	this->angle = 360.0f / this->nrOfPanels;
	this->width = -(GLfloat)(sin(this->angle * 0.5f)) * this->raio * 2.0f;
	this->primeiraVez = true;
}

cenario::cenario(ODETrack * trk)
{

	GLfloat lines = trk->getLength();
	GLfloat columns = trk->getWidth();
	GLfloat blockSize = trk->getSegment(0,0).getSize()[0];
	this->height = 140.0;
	this->nrOfPanels = 8;

	(lines > columns) ? this->width = lines * blockSize : this->width = columns * blockSize;
	this->raio = this->width;
	this->angle = 360.0f / this->nrOfPanels;
	this->width = -(GLfloat)(sin(this->angle * 0.5f)) * this->raio * 2.0f;
	this->primeiraVez = true;
	this->track = trk;
}

cenario::~cenario()
{
	texture.~textura();
}


void cenario::desenha()
{
	if(this->primeiraVez)
	{
		this->loadTexture();
		this->geraDL();
		this->primeiraVez = false;
	}

	glPushMatrix();
		glTranslatef(this->raio * 0.5,-this->raio * 0.2, -this->height * 0.3f);
		glRotatef(90.0,1.0f,0.0f,0.0f);
		glCallList(this->dlCenario);
	glPopMatrix();
}

void cenario::geraDL()
{
	// Create o id para a lista
	this->dlCenario = glGenLists(1);
	
	// inicializa a lista
	glNewList(this->dlCenario,GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		desenhaAux();
	// termina a lista
	glEndList();
}

void cenario::desenhaAux()
{
	GLfloat txBegin = 0.0;
	GLfloat txEnd = 1.0 / this->nrOfPanels;
	GLfloat slack = 1.0 / this->nrOfPanels;

	glPushMatrix();
		glPushMatrix();
			for(int i = 0 ; i < this->nrOfPanels ; i++)
			{
				glPushMatrix();
					glRotatef((GLfloat)i * this->angle, 0.0f, 1.0f, 0.0f);
					this->desenhaPainel(txBegin,txEnd);
					txBegin += slack;
					txEnd += slack;
				glPopMatrix();
			}
		glPopMatrix();
	glPopMatrix();
	
}

void cenario::desenhaPainel(GLfloat txBegin, GLfloat txEnd)
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
			glTranslatef(0.0f, 0.0f, this->raio * 1.15);
			glColor3f(0.2f, 0.2f, 0.2f);
			glPushMatrix();
				glTranslatef(-this->width * 0.5f, 0.0f, 0.0f);
				glEnable(GL_TEXTURE_2D);
				texture.SetActive();
				glBegin(GL_QUADS);
					glNormal3f(0.0f, 0.0f, 1.0f);
					glTexCoord2f(txBegin , 0.0f);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glTexCoord2f(txEnd, 0.0f);
					glVertex3f(this->width, 0.0f, 0.0f);
					glTexCoord2f(txEnd, 1.0f);
					glVertex3f(this->width, this->height, 0.0f);
					glTexCoord2f(txBegin, 1.0f);
					glVertex3f(0.0f, this->height, 0.0f);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			glPopMatrix();
		glPopMatrix();
}

void cenario::loadTexture()
{
	char buffer[256];
	string temp;
	
	switch(this->track->getGroundSurface())
	{
		case ODETrackSegmentDefinition::Ice :
			temp = "texturas/cenario/gelo.bmp";
		break;

		case ODETrackSegmentDefinition::Snow :
			temp = "texturas/cenario/neve.bmp";
		break;

		case ODETrackSegmentDefinition::Gravel :
			temp = "texturas/cenario/gelo.bmp";
		break;

		case ODETrackSegmentDefinition::Grass :
			temp = "texturas/cenario/neve.bmp";
		break;

		default:
			temp = "texturas/cenario/floresta.bmp";
		break;
	}
	
	strncpy(buffer, temp.c_str(), 255);
	texture.LoadTextures(buffer);

}