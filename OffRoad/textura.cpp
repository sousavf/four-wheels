#include "textura.h"

#pragma warning(disable: 4996)

textura::~textura()
{
	//glDeleteTextures(1,&this->ID);
}

AUX_RGBImageRec *textura::LoadBMP(const char *Ficheiro)
{
	FILE *File=NULL;
	
	if (!Ficheiro)								
	{
		return NULL;							
	}

	File=fopen(Ficheiro,"r");

	if (File)								
	{
		fclose(File);							
		return auxDIBImageLoadA(Ficheiro);				
	}

	return NULL;
}


int textura::LoadTextures(const char *filename)
{
	int Status=FALSE;
	GLuint Num;
	AUX_RGBImageRec *TextureImage[1];

	memset(TextureImage,0,sizeof(void *)*1);

	if (TextureImage[0]=LoadBMP(filename))
	{
		Status=TRUE;
		glGenTextures(1, &Num);
		glBindTexture(GL_TEXTURE_2D, Num);
	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		/*glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY
			, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);*/
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	if (TextureImage[0])							
	{
		if (TextureImage[0]->data)			
		{
			this->SetID(Num);
			free(TextureImage[0]->data);				
		}

		free(TextureImage[0]);						
	}

	return Status;

}

void textura::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, this->GetID());
}

GLuint textura::GetID()
{
	return ID;
}

void textura::SetID(GLuint Novo_Valor)
{
	this->ID=Novo_Valor;
}
