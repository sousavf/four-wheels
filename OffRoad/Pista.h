#ifndef PISTA_
#define PISTA_

#include "Segmento.h"
#include "ODERequirements.h"
#include "ODEHeaders.h"
#include <vector>
#include "textura.h"
#include <Math.h>
#include "Rails.h"
#include "Arvore.h"
#include <string>

using namespace ODE;
using namespace std;

class Pista
{
	private:
		Segmento **Circuito;
		GLint StartX,StartY,StartZ;
		GLfloat TamanhoBloco;
		GLuint DLMeta;
		textura Bandeira,Poste;
		int Width;
		int Heigth;

		static const char* getTextura(ODETrackSegmentDefinition::Block b);
		const GLuint getDLCall(ODETrackSegmentDefinition::Block b);
		GLuint geraDLMeta();

		// Variavel das DL'S dos varios tipos da Pista
		GLuint TipoCircuito[14];
	
		void initText();
		void desenhaMeta();
		void GeraSegmento(char *text, GLint N_Div, GLfloat TamanhoBlocoX, GLfloat TamanhoBlocoY,int type);
		GLuint geraDLSegmento(char *text,GLint N_Div, GLfloat TamanhoBloco,int type);
		GLuint geraDLRampa(char *text, GLfloat altura,GLfloat rotacao,int type);

	public:
		Pista();
		~Pista();
		void desenha();
		void init(const ODETrack &track);
		void CarregaPista(const ODETrack &track);
		void setStart(GLfloat x,GLfloat y,GLfloat z);
		void setTamanhoBloco(GLfloat size);
};

#endif