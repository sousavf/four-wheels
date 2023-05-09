#include "velocimetro.h"

Velocimetro::Velocimetro()
{
	
}

void Velocimetro::init()
{
	this->Fundo.LoadTextures("texturas/velocimetro/limite.bmp");
	this->Limite.LoadTextures("texturas/velocimetro/fundo.bmp");
	this->Ponteiro.LoadTextures("texturas/velocimetro/ponteiro.bmp");
}


void Velocimetro::desenha(const int Speed,int w,int h)
{
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	GLfloat t,x,y,a,b;

	t = M_PI*(GLfloat)Speed/45;

	glViewport(w-(w/4), 0, w/4, h/4);
	//glDisable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0,1,0,1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();

				//gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);

				//glScalef(300.0f,300.0f,1.0f);
				glTranslatef(0.5f,0.5f,0.0f);
				glRotatef(150.0f,0.0f,0.0f,1.0f);

				// Ponteiro

				glLineWidth(1.0f);
				glBegin(GL_LINES);

				Ponteiro.SetActive();
				
				glColor3f(1.0f,1.0f,0.0f);
					a = cos(-t+0.5*M_PI);
					b = sin(-t+0.5*M_PI);
					x=0.35*a;// Tamanho do ponteiro
					y=0.35*b;
				glVertex2f(x,y);

					x = -0.01f;
					y = -0.04f;
				glColor3f(1.0f,1.0f,1.0f);
				glVertex2f(x,y);
				glEnd();

				Limite.SetActive();
				poligono(40,0,0,0.38,0.5f,0.5f,0.5f); // Circulo Exterior
				Fundo.SetActive();
				poligono(40,0,0,0.40,1.0f,1.0f,1.0f); // Circulo Interior

			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glViewport(0, 0, w, h);
}

void Velocimetro::poligono(GLint n, GLfloat x0, GLfloat y0, GLfloat r, GLfloat red, GLfloat green, GLfloat blue)
{
	GLint i;
	GLfloat t,x,y;

	glLineWidth(4.5);
	glBegin(GL_POLYGON);
	for(i=0;i<n;i++)
	{
		t = 2.0*M_PI*(GLfloat)i/(GLfloat)n;
		x = r * cos(t) + x0;
		y = r * sin(t) + y0;
		glColor3f(red,green,blue);
		glVertex2f(x,y);
	}
	glEnd();
}
