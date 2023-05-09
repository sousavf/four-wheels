#ifndef MENU_H
#define MENU_H

#define NR_TEXTURAS_MENU 14
#define NR_VEICULOS 2
#define MAX_PISTAS 10
#define NR_OP_CONFIGURACAO 2
#define NR_RESOLUCOES 2
#define NR_SONS 1
#define NR_NR_VOLTAS 4

#include "../textura.h"
#include "../pista.h"
#include "../Carro/veiculo.h"
#include "../glf/glf.h"
#include "../weather.h"
#include "ODERequirements.h"
#include "ODEHeaders.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>

#include <fmod.h>
#include <fmod_errors.h>
#ifdef WIN32
	#include <windows.h>
	#pragma comment(lib,"fmod/lib/fmod.lib")
#else
	#include <wincompat.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace ODE;

struct veiculoData
{
	char* nome;
	veiculo *veic;
	veiculo *veicNeve;
};

struct pistaData
{
	char * nome;
	string ficheiro;
	ODETrack *pistaODE;
	Pista * track;
};

class menu
{
	private:

		//------------
		GLfloat raio;
		GLfloat sectores;
		GLfloat alturaPainel;
		GLfloat anguloSectores;
		GLfloat larguraPainel;//guarda a largura do painel onde vai ser mostrada a opcao no menu principal
		GLfloat ang;
		GLint opcaoSeleccionada;
		GLint submenuActivo;

		ODESimulation mundo;

		string pathTexturas;
		textura texturas[NR_TEXTURAS_MENU];
		string texNames[NR_TEXTURAS_MENU];
		
		veiculoData veiculos[NR_VEICULOS];
		pistaData pistas[MAX_PISTAS];

		int veiculoSeleccionado;
		int pistaSeleccionada;
		int nrPistas;
		int opcaoConfiguracaoSeleccionada;
		int resolucaoSeleccionada;
		int font;//guarda o nr da fonte
		int nrVoltasSeleccionado;

		string resolucoes[NR_RESOLUCOES];
		char * nrVoltas[NR_NR_VOLTAS];

		//variaveis de controlo
		bool aRodarPraEsquerda;
		bool aRodarPraDireita;
		bool estaPistaSeleccionada;
		bool estaVeiculoSeleccionado;
		bool estaCondicaoAtmosfericaSeleccionada;
		bool estaNrVoltasSeleccionado;
		bool flagMostraMoldura;
		bool flagMostraLinha;
		bool flagMostraTeclas;
		bool iniciaJogo;
		bool primeiraVez;

		int frames;

		GLfloat angRodado;
		
		char * condicoesAtmosfericas[4];
		int condicaoAtmosfericaSeleccionada;
		int nrCondicoesAtmosfericas;

		long contaRenderizacoes;

		void initTextNames();
		void loadTextures();
	
		void carregaPistas();//metodo responsavel por carregar todas as pistas

		void desenhaOpcaoMenuPrincipal(textura tx);
		void desenhaOpcoesMenuPrincipal(int);
		void rodaMenu(GLfloat angulo);
		void desenhaMoldura();
		void desenhaLinha();

		void desenhaMenuPrincipal();
		void desenhaFundo(textura tx);
		void desenhaBotao();
		void desenhaSeta(GLfloat y);
		void desenhaSeleccionador(GLfloat x, GLfloat y);
		void desenhaMelhorTempo();
		void desenhaNovoJogo();//metodo responsavel po desenhar o menu para iniciar um novo jogo
		void desenhaMenuOpcoes();
		
		void animaMenu();//funcao responsavel por rodar o menu
		
		void voltaAoPrincipal();
		void abreMenu();

		string resolucaoAnterior;

	public:
		menu(GLfloat r, GLfloat sec, GLfloat altPainel);
		~menu();

		void anterior();
		void proximo();
		void cima();
		void baixo();
		void pressEnter();
		void pressEscape();
		bool getJogo();
		veiculo * getVeiculo();
		const char * getPista();
		ODESimulation& getMundo();
		void desenha();
		void destroy();
		void iniciaMenu();
		weather getWeather();
		int getNrVoltas();
		string getResolution() const;
		string getOldResolution() const;
		void restart();
		GLint getMenuActivo();
};

#endif