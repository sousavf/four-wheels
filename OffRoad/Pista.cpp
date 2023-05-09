#include "pista.h"

#pragma warning(disable: 4996)

Pista::Pista()
{
	
}

Pista::~Pista()
{
	for(int i = 0 ; i < 6 ; i++)
		glDeleteLists(this->TipoCircuito[i],1);
	
	for(int i = 0 ; i < this->Heigth ; i++)
	{
		for(int j = 0 ; j < this->Width ; j++)
			this->Circuito[i][j].~Segmento();
		delete[] this->Circuito[i];
	}
	delete[] this->Circuito;
}

void Pista::CarregaPista(const ODETrack &track)
{
	ODEVector3 Posicao;

	Circuito = new Segmento*[track.getLength()];

	this->setTamanhoBloco(track.getSegment(0,0).getSize()[0]);
	this->setStart(track.getStartLine().getPosition()[1],-track.getStartLine().getPosition()[0],track.getStartLine().getPosition()[2]);

	this->init(track);

	this->Width = track.getWidth();
	this->Heigth = track.getLength();

	for(int y = 0; y < track.getLength(); y++)
	{
		Circuito[y] = new Segmento[track.getWidth()];

		for(int x = 0; x < track.getWidth(); x++)
		{
			Posicao = track.getSegment(x,y).getPosition();
			Circuito[y][x].SetX(Posicao[1]);
			Circuito[y][x].SetY(-Posicao[0]);
			Circuito[y][x].SetZ(Posicao[2]);
			Circuito[y][x].SetSize(track.getSegment(x,y).getSize()[0]);
			Circuito[y][x].SetDLCall(getDLCall(track.getSegment(x,y).getType()));
		}
	}
}

void Pista::desenha()
{
	GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glEnable(GL_TEXTURE_2D);
	glCallList(this->DLMeta);

	for(int y = 0; y < this->Heigth; y++)
	{
		for(int x = 0; x < this->Width; x++)
		{
			Circuito[y][x].desenha();
		}
	}
}

void Pista::setStart(GLfloat x,GLfloat y,GLfloat z)
{
	this->StartX = x;
	this->StartY = y;
	this->StartZ = z;
}

/// Inicializa as texturas para a meta e
/// gera a display list da meta.
/// Inicializa as DL'S da pista
void Pista::init(const ODETrack &track)
{
	string dir,file,path;
	char buffer[256];
	GLfloat div = 55;

	this->initText();

	this->DLMeta = this->geraDLMeta();

	switch(track.getGroundSurface())
	{
	case ODETrackSegmentDefinition::Gravel: // Gravilha
	dir = "texturas/pista/gravel/";
	break;

	case ODETrackSegmentDefinition::Grass: // Relva
	dir = "texturas/pista/grass/";
	break;

	case ODETrackSegmentDefinition::Snow: // Neve
	dir = "texturas/pista/snow/";
	break;

	case ODETrackSegmentDefinition::Ice: // Gelo
	dir = "texturas/pista/ice/";
	break;
	}

	// StartStraightBack StartStraightFront Straight
	file = "STRAIGHT_SIDE.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[0] = this->geraDLSegmento(buffer,div,this->TamanhoBloco,0);
	
	// StartStraightLeft StartStraightRight StraightSide
	file = "STRAIGHT.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[1] = this->geraDLSegmento(buffer,div,this->TamanhoBloco,1);
	
	// Curve90BottomToRight
	file = "CURVE_90_TOP_TO_RIGHT.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[2] = this->geraDLSegmento(buffer,div,this->TamanhoBloco,2);
	
	// Curve90LeftToBottom
	file = "CURVE_90_LEFT_TO_TOP.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[3] = this->geraDLSegmento(buffer,div,this->TamanhoBloco,3);
	
	// Curve90LeftToTop
	file = "CURVE_90_LEFT_TO_BOTTOM.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[4] = this->geraDLSegmento(buffer,div,this->TamanhoBloco,4);
	
	// Curve90BottomToRight
	file = "CURVE_90_BOTTOM_TO_RIGHT.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[5] = this->geraDLSegmento(buffer,div,this->TamanhoBloco,5);


	GLfloat altura = 1.0f;

	// RampStraightElevated
	file = "STRAIGHT.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[6] = this->geraDLRampa(buffer,altura ,0.0f,1);

	// RampStraightSunken
	file = "STRAIGHT.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[7] = this->geraDLRampa(buffer,-altura ,0.0f,1);

	// RampStraightElevated
	file = "STRAIGHT.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[8] = this->geraDLRampa(buffer,altura ,1.0f,1);

	// RampStraightSunken
	file = "STRAIGHT.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[9] = this->geraDLRampa(buffer,-altura ,1.0f,1);

	// Grass
	file = "default.bmp";
	path = dir + file;
	strncpy(buffer, path.c_str(), 255);
	this->TipoCircuito[10] = this->geraDLSegmento(buffer, div,this->TamanhoBloco,-1);
}

void Pista::initText()
{
	this->Bandeira.LoadTextures("texturas/meta/bandeira.bmp");
	this->Poste.LoadTextures("texturas/meta/poste.bmp");
}


GLuint Pista::geraDLMeta()
{
	GLuint lista;

	// Create o id para a lista
	lista = glGenLists(1);
	
	// inicializa a lista
	glNewList(lista,GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		this->desenhaMeta();

	// termina a lista
	glEndList();
	
	return(lista);
}

GLuint Pista::geraDLSegmento(char *text,GLint N_Div, GLfloat TamanhoBloco, int type)
{
	GLuint lista;

	// Create o id para a lista
	lista = glGenLists(1);
	
	// inicializa a lista
	glNewList(lista,GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		this->GeraSegmento(text,N_Div,TamanhoBloco,TamanhoBloco,type);

	// termina a lista
	glEndList();
	
	return(lista);
}

GLuint Pista::geraDLRampa(char *text, GLfloat altura,GLfloat rotacao, int type)
{
	GLuint lista;
	GLfloat angulo, comprimento;

	// Create o id para a lista
	lista = glGenLists(1);
	
	// inicializa a lista
	glNewList(lista,GL_COMPILE);


	// Calculos para ver o angulo da rampa
	
	// hipotenusa
	comprimento = sqrt ( pow(this->TamanhoBloco * 0.5, 2)+ pow(altura, 2) );

	// angulo
	angulo  = acos(((this->TamanhoBloco * 0.5)/comprimento));


	angulo = angulo * (180 / M_PI);

	comprimento += 0.5f;


	// chamada da funcao que contem 
	// os comandos de renderização
	if(altura>0)
	{
		if(rotacao != 0 )
			glRotatef(90,0.0f,0.0f,rotacao);
			
		glPushMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f , 0.5f * altura);
				glTranslatef(0.0f , this->TamanhoBloco * 0.25f  , 0.0f);
				glRotatef(-angulo, 1.0f, 0.0f, 0.0f);
				this->GeraSegmento(text,55,TamanhoBloco,comprimento,type);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f , 0.5f * altura);
				glTranslatef(0.0f , -this->TamanhoBloco * 0.25f  , 0.0f);
				glRotatef(angulo , 1.0f, 0.0f, 0.0f);
				this->GeraSegmento(text,55, TamanhoBloco , comprimento,type);
			glPopMatrix();
		glPopMatrix();
	}
	else
	{
		if(rotacao != 0)
			glRotatef(90,0.0f,0.0f,rotacao);

		glPushMatrix();
			//glRotatef(180, 0.0f, rotacao,0.0f);
			glPushMatrix();	
				glTranslatef(0.0f, 0.0f, 0.5f * altura);				
				glTranslatef(0.0f , this->TamanhoBloco * 0.25f, 0.0f);
				glRotatef(angulo, 1.0f, 0.0f, 0.0f);
				this->GeraSegmento(text,55, TamanhoBloco, comprimento,type);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, 0.5f * altura);
				glTranslatef(0.0f, - this->TamanhoBloco * 0.25f, 0.0f);			
				glRotatef(- angulo, 1.0f, 0.0f, 0.0f);
				this->GeraSegmento(text,55, TamanhoBloco, comprimento,type);
			glPopMatrix();
		glPopMatrix();
	}
	// termina a lista
	glEndList();
	
	return(lista);
}

void Pista::GeraSegmento(char *text, GLint N_Div, GLfloat TamanhoBlocoX, GLfloat TamanhoBlocoY, int type)
{
	textura aplicar;
	Rails Limite;
	Arvore Arvorezita;
	GLfloat AcresceX,AcresceY,DivText,X,Y;
	GLfloat Startx,Starty;
	GLfloat cor[3]={0.1f,0.0f,0.0f}; 

	Limite.init();

	AcresceX = TamanhoBlocoX / N_Div ;
	AcresceY = TamanhoBlocoY / N_Div ;

	DivText = 1.0f / N_Div;

	aplicar.LoadTextures(text);

	glEnable(GL_TEXTURE_2D);
	
	aplicar.SetActive();

	glPushMatrix();
		glBegin(GL_QUADS);
			for(int y=1; y<=N_Div;y++)
			{
				Startx = 0 - (TamanhoBlocoX * 0.5);
				Starty = 0 + (TamanhoBlocoY * 0.5) - y * AcresceY;

				for(int x=1;x<=N_Div;x++)
				{
					glColor3fv(cor);
					glNormal3f(0.0f,0.0f,1.0f);
					
					// 1º

					X=x * DivText - DivText;
					Y=y * DivText - DivText;

					glTexCoord2f(X,Y);
					glVertex3f(Startx, Starty, 0);

					// 2º

					X=x * DivText - DivText;
					Y=y * DivText;

					glTexCoord2f(X,Y);
					glVertex3f(Startx + AcresceX,Starty, 0);

					// 3º

					X=x * DivText;
					Y=y * DivText;

					glTexCoord2f(X,Y);
					glVertex3f(Startx + AcresceX,Starty - AcresceY , 0);

					// 4º

					X=x * DivText;
					Y=y * DivText - DivText;

					glTexCoord2f(X,Y);
					glVertex3d(Startx,Starty - AcresceY, 0);

					Startx += AcresceX;
				}
			}
		glEnd();
	glPopMatrix();

	Limite.desenha(TamanhoBlocoY,type); // rail

	// Arvores
	if(type == -1) // Só relva
	{
		Arvorezita.init();
		glPushMatrix();
			glTranslatef(2.0f, -2.0f, 0.0f);
			Arvorezita.desenha();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-7.0f, 3.0f, 0.0f);
			Arvorezita.desenha();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f, -5.0f, 0.0f);
			Arvorezita.desenha();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(5.0f, 7.0f, 0.0f);
			Arvorezita.desenha();
		glPopMatrix();
	}	
	glDisable(GL_TEXTURE_2D);
}


void Pista::desenhaMeta()
{
	GLfloat cor[3]={1.0f,1.0f,1.0f}; 
	GLfloat LarguraPoste = 0.25f;
	GLfloat AlturaPoste = 3.5f;
	GLfloat AlturaBandeira = 2.0f;

	glEnable(GL_TEXTURE_2D);

	this->Bandeira.SetActive();

	glPushMatrix();
		glBegin(GL_QUADS);
			
			glColor3fv(cor);
			glNormal3f(0.0f,0.0f,1.0f);

			

			// 1º Poste

			glVertex3f(this->StartX , this->StartY + this->TamanhoBloco / 2 , this->StartZ);
			glVertex3f(this->StartX + LarguraPoste , this->StartY + this->TamanhoBloco / 2  , this->StartZ);
			glVertex3f(this->StartX + LarguraPoste, this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);
			glVertex3f(this->StartX , this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);

			// 2º Poste

			glVertex3f(this->StartX , this->StartY - this->TamanhoBloco / 2 , this->StartZ);
			glVertex3f(this->StartX + LarguraPoste , this->StartY - this->TamanhoBloco / 2  , this->StartZ);
			glVertex3f(this->StartX + LarguraPoste , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);
			glVertex3f(this->StartX , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);


			// Bandeira
			
			// Faixa Grande Frente
			glTexCoord2f(0.0,0.0);
			glVertex3f(this->StartX , this->StartY + this->TamanhoBloco / 2 , this->StartZ + AlturaPoste);
			glTexCoord2f(1.0,0.0);
			glVertex3f(this->StartX , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);
			glTexCoord2f(1.0,1.0);
			glVertex3f(this->StartX , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);
			glTexCoord2f(0.0,1.0);
			glVertex3f(this->StartX , this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);


			// Faixa Grande Trâs
			glTexCoord2f(0.0,0.0);
			glVertex3f(this->StartX + LarguraPoste , this->StartY + this->TamanhoBloco / 2 , this->StartZ + AlturaPoste);
			glTexCoord2f(1.0,0.0);
			glVertex3f(this->StartX + LarguraPoste , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);
			glTexCoord2f(1.0,1.0);
			glVertex3f(this->StartX + LarguraPoste , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);
			glTexCoord2f(0.0,1.0);
			glVertex3f(this->StartX + LarguraPoste , this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);

			// Limite Esquerda
			
			glVertex3f(this->StartX , this->StartY - this->TamanhoBloco / 2 , this->StartZ + AlturaPoste);
			glVertex3f(this->StartX + LarguraPoste , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);
			glVertex3f(this->StartX + LarguraPoste , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);
			glVertex3f(this->StartX , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);
			

			// Limite Direita
			
			glVertex3f(this->StartX , this->StartY + this->TamanhoBloco / 2 , this->StartZ + AlturaPoste);
			glVertex3f(this->StartX + LarguraPoste , this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste);
			glVertex3f(this->StartX + LarguraPoste , this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);
			glVertex3f(this->StartX , this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);

			// Parte Superior

			glVertex3f(this->StartX , this->StartY + this->TamanhoBloco / 2 , this->StartZ + AlturaPoste + AlturaBandeira);
			glVertex3f(this->StartX + LarguraPoste , this->StartY + this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);
			glVertex3f(this->StartX + LarguraPoste , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);
			glVertex3f(this->StartX , this->StartY - this->TamanhoBloco / 2  , this->StartZ + AlturaPoste + AlturaBandeira);

		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Pista::setTamanhoBloco(GLfloat size)
{
	this->TamanhoBloco = size;
}

const char* Pista::getTextura(ODETrackSegmentDefinition::Block b)
{
	switch (b)
	{
		case ODETrackSegmentDefinition::StartStraightBack:
		case ODETrackSegmentDefinition::StartStraightFront:
		case ODETrackSegmentDefinition::Straight:  
			return "texturas/pista/terra/STRAIGHT_SIDE.bmp";

		case ODETrackSegmentDefinition::StartStraightLeft:
		case ODETrackSegmentDefinition::StartStraightRight:
		case ODETrackSegmentDefinition::StraightSide:  
			return "texturas/pista/terra/STRAIGHT.bmp";

		case ODETrackSegmentDefinition::Curve90BottomToRight:
			return "texturas/pista/terra/CURVE_90_TOP_TO_RIGHT.bmp";

		case ODETrackSegmentDefinition::Curve90LeftToBottom:
			return "texturas/pista/terra/CURVE_90_LEFT_TO_TOP.bmp";

		case ODETrackSegmentDefinition::Curve90LeftToTop:
			return "texturas/pista/terra/CURVE_90_LEFT_TO_BOTTOM.bmp";

		case ODETrackSegmentDefinition::Curve90TopToRight:
			return "texturas/pista/terra/CURVE_90_BOTTOM_TO_RIGHT.bmp";

		case ODETrackSegmentDefinition::Empty:
		default:
			return "Empty";
	}
}

const GLuint Pista::getDLCall(ODETrackSegmentDefinition::Block b)
{

	switch (b)
	{
		case ODETrackSegmentDefinition::StartStraightBack:
		case ODETrackSegmentDefinition::StartStraightFront:
		case ODETrackSegmentDefinition::Straight:  
			return this->TipoCircuito[0];

		case ODETrackSegmentDefinition::StartStraightLeft:
		case ODETrackSegmentDefinition::StartStraightRight:
		case ODETrackSegmentDefinition::StraightSide:  
			return this->TipoCircuito[1];

		case ODETrackSegmentDefinition::Curve90BottomToRight:
			return this->TipoCircuito[2];

		case ODETrackSegmentDefinition::Curve90LeftToBottom:
			return this->TipoCircuito[3];

		case ODETrackSegmentDefinition::Curve90LeftToTop:
			return this->TipoCircuito[4];

		case ODETrackSegmentDefinition::Curve90TopToRight:
			return this->TipoCircuito[5];

		case ODETrackSegmentDefinition::RampStraightSideElevated:
			return this->TipoCircuito[6];

		case ODETrackSegmentDefinition::RampStraightSideSunken:
			return this->TipoCircuito[7];

		case ODETrackSegmentDefinition::RampStraightElevated:
			return this->TipoCircuito[8];

		case ODETrackSegmentDefinition::RampStraightSunken:
			return this->TipoCircuito[9];

		case ODETrackSegmentDefinition::Empty:
		default:
			return this->TipoCircuito[10];
	}
}
