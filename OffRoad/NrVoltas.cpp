#include "NrVoltas.h"

#pragma warning(disable: 4996)

NrVoltas::NrVoltas()
{

}

void NrVoltas::desenha(int VoltaActual,int VoltasTotal, int w, int h)
{
	char buffer[256];
	char voltaAct[10];
	char voltaTot[10];

	itoa(VoltaActual, voltaAct, 10);
	itoa(VoltasTotal, voltaTot, 10);
	strcpy(buffer, voltaAct);
	strcat(buffer, " / ");
	strcat(buffer, voltaTot);

	glfLoadFont("fonts/arial1.glf");

	
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glViewport(w-(w/6), h-(h/6), w/6, h/6);
	//glDisable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0,1,0,1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
				glPushMatrix();
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(0.5f, 0.85f, 0.0f);
					glfStringDirection(GLF_CENTER);
					glScalef(0.1f, 0.1f, 0.1f);
					glfDrawSolidString(buffer);
				glPopMatrix();
				glColor3f(0.3f, 0.3f, 0.3f);
				glRectf(0.30f, 0.70f, 1.25f, 1.25f);
				glColor3f(1.0f, 1.0f, 1.0f);
				glRectf(0.27f, 0.65f, 1.25f, 1.25f);
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