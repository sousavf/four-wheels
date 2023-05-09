#ifndef TEXTURA_
#define TEXTURA_

#include	<windows.h>							
#include	<stdio.h>							
#include    <iostream>
#include	<gl\gl.h>							
#include	<gl\glu.h>							
#include	<gl\glaux.h>

using namespace std;

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glaux.lib")

class textura
{
	public:
		~textura();
		GLuint GetID();
		AUX_RGBImageRec *LoadBMP(const char *filename);
		int LoadTextures(const char *filename);
		void SetActive();
		void SetID(GLuint Novo_Valor);


	private:
		GLuint ID;
};

#endif
