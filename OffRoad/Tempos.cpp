#include "Tempos.h"
#include "Records.h"

#pragma warning(disable: 4996)

Tempos::Tempos()
{
}



Tempos::~Tempos()
{
}



void Tempos::desenha(const LapCounter &counter, int w, int h)
{
	char minutos[3], segundos[3], buffer[20], volta[2];

	glfLoadFont("fonts/arial1.glf");
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glViewport(0, h/2, w/4, h/2);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0,1,0,1);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
				glLoadIdentity();
				glPushMatrix();
					glColor3f(0.0f, 0.0f, 0.0f);
					glfStringDirection(GLF_LEFT);
					glTranslatef(0.1f, 0.95f, 0.0f);
					glScalef(0.04f, 0.04f, 0.04f);
					int i;

					for (i = 0; i < counter.getLaps(); i++)
					{
						Time time = Records::toTime(counter.getTime(i));
						itoa(time.minutes, minutos, 10);
						itoa(time.seconds, segundos, 10);
						itoa(i + 1, volta, 10);
						strcpy(buffer, volta);
						strcat(buffer, " -\t");

						if (time.minutes < 10)
						{
							strcat(buffer, "0");
						}
						strcat(buffer, minutos);
						strcat(buffer, ":");

						if (time.seconds < 10)
						{
							strcat(buffer, "0");
						}
						strcat(buffer, segundos);
						glPushMatrix();
							glTranslatef(0.0f, -i * 1.65f, 0.0f);
							glfDrawSolidString(buffer);
						glPopMatrix();
					}
					Time time = Records::toTime(counter.getCurrentTime());
					itoa(time.minutes, minutos, 10);
					itoa(time.seconds, segundos, 10);
					itoa(i + 1, volta, 10);
					strcpy(buffer, volta);
					strcat(buffer, " -\t");
					
					if (time.minutes < 10)
					{
						strcat(buffer, "0");
					}
					strcat(buffer, minutos);
					strcat(buffer, ":");

					if (time.seconds < 10)
					{
						strcat(buffer, "0");
					}
					strcat(buffer, segundos);
					glTranslatef(0.0f, -i * 1.65f, 0.0f);
					glfDrawSolidString(buffer);
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