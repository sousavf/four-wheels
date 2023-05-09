#include "geraPoligono.h"

void geraPoligono::disk()
{
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluDisk(qobj, 0.5, 1.5, 20, 10);
	gluDeleteQuadric(qobj);
}

void geraPoligono::cilindroFechado(GLdouble loops ,GLdouble outterRadius, GLdouble height, GLdouble slices, GLdouble stacks)
{
	cilindroAberto(loops ,0.0f, outterRadius, height, slices, stacks);
}

void geraPoligono::cilindroAberto(GLdouble loops ,GLdouble innerRadius, GLdouble outterRadius, GLdouble height, GLdouble slices, GLdouble stacks)
{
	
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); //GLU_LINE //GLU_FILL
	gluQuadricNormals(qobj, GLU_SMOOTH);
		gluDisk(qobj, innerRadius, outterRadius, slices, loops);
		gluCylinder(qobj, outterRadius, outterRadius, height, slices, stacks);
		glTranslatef(0, 0, height);
		gluDisk(qobj, innerRadius, outterRadius, slices, loops);
	gluDeleteQuadric(qobj);
}
void geraPoligono::esfera(GLfloat radius, GLfloat slices, GLfloat stacks)
{
	GLUquadricObj* qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GL_FILL); 
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluSphere(qobj, radius, slices, stacks);
	gluDeleteQuadric(qobj);
}

void geraPoligono::triangulo(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
}
void geraPoligono::triangulo(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat nx, GLfloat ny, GLfloat nz)
{
	glBegin(GL_TRIANGLES);
		glNormal3f(nx, ny, nz);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
}

void geraPoligono::cubo(GLfloat largura, GLfloat comprimento, GLfloat altura)
{
	glPushMatrix();
		glPushMatrix();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(comprimento, 0.0f, 0.0f);
				glVertex3f(comprimento, altura, 0.0f);
				glVertex3f(0.0f, altura, 0.0f);
			glEnd();
			//glRectf(0.0f, 0.0f, comprimento, altura);
			glTranslatef(0.0f,0.0f, -largura);
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(comprimento, 0.0f, 0.0f);
				glVertex3f(comprimento, altura, 0.0f);
				glVertex3f(0.0f, altura, 0.0f);
			glEnd();
			//glRectf(0.0f, 0.0f, comprimento, altura);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f,0.0f, -largura);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -altura);
					glBegin(GL_QUADS);
						glNormal3f(0.0f, 0.0f, -1.0f);
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f(comprimento, 0.0f, 0.0f);
						glVertex3f(comprimento, largura, 0.0f);
						glVertex3f(0.0f, largura, 0.0f);
					glEnd();
					//glRectf(0.0f,0.0f,comprimento, largura);
				glPopMatrix();
				glPushMatrix();
					glBegin(GL_QUADS);
						glNormal3f(0.0f, 0.0f, 1.0f);
						glVertex3f(0.0f, 0.0f, 0.0f);
						glVertex3f(comprimento, 0.0f, 0.0f);
						glVertex3f(comprimento, largura, 0.0f);
						glVertex3f(0.0f, largura, 0.0f);
					glEnd();
					//glRectf(0.0f,0.0f,comprimento, largura);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(largura, 0.0f, 0.0f);
				glVertex3f(largura, altura, 0.0f);
				glVertex3f(0.0f, altura, 0.0f);
			glEnd();
			//glRectf(0.0f,0.0f,largura, altura);
			glTranslatef(0.0f, 0.0f, comprimento);
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(largura, 0.0f, 0.0f);
				glVertex3f(largura, altura, 0.0f);
				glVertex3f(0.0f, altura, 0.0f);
			glEnd();
			
			//glRectf(0.0f,0.0f,largura, altura);
		glPopMatrix();
	glPopMatrix();
}