#ifndef VEICULO_H
#define VEICULO_H

#include "objecto.h"
#include "roda.h"
#include "definicoes.h"
#include "../textura.h"
#include "../weather.h"
#include <stdlib.h>
#include<GL/glut.h>
#include<GL/glaux.h>
#include<math.h>
#include <iostream>
#include<string>
using namespace std;

struct r //estrutura para as rodas
{
	roda f_esq;
	roda f_dir;
	roda t_esq;
	roda t_dir;
};

class veiculo : public objecto
{
	private:
		GLfloat altura;
		GLfloat largura;
		GLfloat comprimento;

		GLfloat distanciaCavaRodaAFrente;
		GLfloat distanciaCavaRodaATras;
		GLfloat distanciaRodaAoChassis;
		GLfloat distanciaEixoAoChassis;
		
		//cavas das rodas
		GLfloat comprimentoCavaDaRoda;
		GLfloat larguraCavaDaRoda;
		GLfloat alturaCavaDaRoda;
		
		//capot
		GLfloat alturaCapot;
		GLfloat comprimentoCapot;
		GLfloat larguraTopoCapot;
		
		//cabine
		GLfloat comprimentoCabine;
		
		//caixa
		GLfloat comprimentoCaixa;

		//rodas
		r rodas;
		roda suplente;
		
		//porta
		GLfloat angPorta;

		//eixo
		GLfloat raioEixo;

		GLint dl_carroceria;
		
		//texturas
		textura texturas[12];
		string texNames[12];
		string pathTexturas;

		//Materiais
		GLfloat shininess[1];
		
		//guarda a cor do veiculo
		GLfloat cor[3];
		//guarda a cor da jante
		GLfloat corJante[3];

		//array com o tremor do veiculo
		GLfloat tremor[3];
		int contaTranslacoes;

		//variáveis de controlo
		bool flagTexturas;
		bool flagTexturesLoaded;
		
		bool flagATravar;
		bool flagAVirarParaAEsquerda;
		bool flagAVirarParaADireita;

		//------------------------------------------------------------
		//Métodos

		//criacao de displayLists
		void geraDLCarroceria();
		
		//funcao que carrega as texturas em memoria
		//tanto as das rodas como as do veiculo
		void loadTextures();

		//desenho de componentes do veiculo(funcoes auxiliares das listadas abaixo destas)
		void desenhaPainelLateralCentral();
		void desenhaCavaDaRoda(GLfloat x);// x = 1 se for para manter as normais por defeito, x = -1 se for para trocar as normais
		void desenhaCavasDasRodas();
		void desenhaFrenteAteMeio();
		void desenhaTraseiraAteMeio();
		void desenhaCapot();
		void desenhaCabine();
		void desenhaCaixa();
		void desenhaJanelaCabine(GLfloat x);
		void desenhaParaBrisas();
		void desenhaBanco();
		void desenhaFoco();
		void desenhaBarraCFocos();
		void desenhaStops();

		//desenha a parte de baixo do carro
		void desenhaFundo();
		//desenha o carro até meio(começando de baixo para cima)
		void desenhaMeio();
		//desenha o veiculo de metade para cima
		void desenhaTopo();

		//desenha a carroceria do veiculo
		void desenhaCarroceria();
		//desenha as rodas do veiculo
		void desenhaRodas();
		//desenha os eixos q ligam as rodas
		void desenhaEixos();

		//funcoes auxiliares dos construtores
		void initRodas();
		void initVariaveisDependentes();
		void initTextureFiles();
		void initDisplayLists(); //carrega as display lists

		void virarRodasParaEsquerda();
		void virarRodasParaDireita();

	public:
			veiculo();
			veiculo(GLfloat posX, GLfloat posY, GLfloat posZ, string pathTex, GLfloat coresJante[3]);
			veiculo(string pathTex, GLfloat coresJante[3]);
			veiculo(GLfloat rotX, GLfloat rotY, GLfloat rotZ, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat Comprimento, GLfloat Largura, GLfloat Altura, GLfloat RaioEixo, GLfloat DistanciaCavaRodaAFrente, GLfloat DistanciaCavaRodaATras, string pathTex, GLfloat cores[3], GLfloat coresJante[3]);
			~veiculo();
			
			void virarRodaEsquerda(GLfloat ang_y);
			void virarRodaDireita(GLfloat ang_y);
			void rotacaoRodas(GLfloat ang_z);
			
			//void translacao(GLfloat x, GLfloat y, GLfloat z);
			void initLuzes();
			void virtual desenha();
			void switchTexturasOnOff();
			void pressionaTravao();
			void soltaTravao();
			
			//metodo para fazer o jipe abanar enquanto anda
			void criaSocalco();
			
			//metodos para indicar que o carro esta a virar
			void viraAEsquerda();
			void viraADireita();
			void vaiEmFrente();
			
			//metodos para animar o modelo durante testes
			void mover(GLfloat x, GLfloat y, GLfloat z);
			//funcao para por o modelo a rodar
			void poeARodar();
};

#endif