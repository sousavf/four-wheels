#include "Segmento.h"

Segmento::Segmento()
{

	// Coords onde se vai desenhar
	this->x=0.0;
	this->y=0.0;
	this->z=0.0;
	this->size = 20.0f;
}

Segmento::Segmento(GLfloat x,GLfloat y,GLfloat z, GLfloat size, char * path)
{
	// Coords onde se vai desenhar

	this->x= x;
	this->y= y;
	this->z= z;
	this->size = size;

	this->Textura(path);
}

Segmento::~Segmento()
{

}

void Segmento::Textura(const char * path)
{
//	if(path!="Empty")
		this->Text.LoadTextures(path);
}

void Segmento::SetX(GLfloat val)
{
	this->x=val;
}

void Segmento::SetY(GLfloat val)
{
	this->y=val;
}

void Segmento::SetZ(GLfloat val)
{
	this->z=val;
}

void Segmento::SetSize(GLfloat size)
{
	this->size = size;
}

void Segmento::desenha()
{
	/*GLint N_Div =40;
	GLfloat Acresce,DivText,X,Y;
	GLfloat Startx,Starty;
	GLfloat cor[3]={0.1f,0.0f,0.0f}; 

	Acresce = this->size / N_Div;

	DivText = 1.0f / N_Div;

	glEnable(GL_TEXTURE_2D);
	
	this->Text.SetActive();

	glPushMatrix();
		glBegin(GL_QUADS);
			for(int y=1; y<=N_Div;y++)
			{
				Startx = this->x - (this->size * 0.5);
				Starty = this->y + (this->size * 0.5) - y * Acresce;

				for(int x=1;x<=N_Div;x++)
				{
					glColor3fv(cor);
					glNormal3f(0.0f,0.0f,1.0f);
					
					// 1º

					X=x * DivText - DivText;
					Y=y * DivText - DivText;

					glTexCoord2f(X,Y);
					glVertex3f(Startx, Starty, this->z);

					// 2º

					X=x * DivText - DivText;
					Y=y * DivText;

					glTexCoord2f(X,Y);
					glVertex3f(Startx + Acresce,Starty, this->z);

					// 3º

					X=x * DivText;
					Y=y * DivText;

					glTexCoord2f(X,Y);
					glVertex3f(Startx + Acresce,Starty - Acresce , this->z);

					// 4º

					X=x * DivText;
					Y=y * DivText - DivText;

					glTexCoord2f(X,Y);
					glVertex3d(Startx,Starty - Acresce, this->z);

					Startx += Acresce;				
				}
			}
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);*/
	
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(this->x,this->y,this->z);

		glCallList(this->DLcall);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


GLfloat Segmento::GetSize() const
{
	return this->size;
}

void Segmento::SetDLCall(GLuint val)
{
	this->DLcall = val;
}