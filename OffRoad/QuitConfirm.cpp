#include "QuitConfirm.h"

void QuitConfirm::desenha(int w, int h)
{
	glfLoadFont("fonts/arial1.glf");
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, h / 3, w, h / 3);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0,1,0,1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
				glfStringDirection(GLF_LEFT);
				glScalef(0.02f, 0.05f, 1.0f);
				glColor3f(1.0f, 0.0f, 0.0f);
				glPushMatrix();
					glTranslatef(19.0f, 9.5f, 0.0f);
					glfDrawSolidString("ESC para cancelar.");
				glPopMatrix();
				glPushMatrix();
					glTranslatef(20.0f,7.5f,0.0f);
					glfDrawSolidString("ENTER para sair");
				glPopMatrix();
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