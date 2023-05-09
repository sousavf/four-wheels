#include"veiculo.h"
//#include "roda.h"

#pragma warning(disable: 4996)

veiculo::veiculo()
{
	ang_rot[0] = 0.0f;
	ang_rot[1] = 0.0f;
	ang_rot[2] = 0.0f;
	posicao.x = 0.0f;
	posicao.y = 0.0f;
	posicao.z = 0.0f;
	altura = ALTURA_VEICULO;
	largura = LARGURA_VEICULO;
	comprimento = COMPRIMENTO_VEICULO;
	raioEixo = RAIO_EIXO;
	distanciaCavaRodaAFrente = DISTANCIA_CAVA_DA_RODA_A_FRENTE;
	distanciaCavaRodaATras = DISTANCIA_CAVA_DA_RODA_A_TRAS;
	
	cor[0] = 0.1f;
	cor[1] = 0.3f;
	cor[2] = 0.15f;
	
	corJante[0] = 0.0f;
	corJante[1] = 0.2f;
	corJante[2] = 0.0f;

	flagTexturas = true;

	pathTexturas = "texturas/veiculos/default/";
	
	initVariaveisDependentes();
	initRodas();
	initTextureFiles();
}

veiculo::veiculo(GLfloat posX, GLfloat posY, GLfloat posZ, string pathTex, GLfloat coresJante[3])
{
	ang_rot[0] = 0.0f;
	ang_rot[1] = 0.0f;
	ang_rot[2] = 0.0f;
	posicao.x = posX;
	posicao.y = posY;
	posicao.z = posZ;
	altura = ALTURA_VEICULO;
	largura = LARGURA_VEICULO;
	comprimento = COMPRIMENTO_VEICULO;
	raioEixo = RAIO_EIXO;
	distanciaCavaRodaAFrente = DISTANCIA_CAVA_DA_RODA_A_FRENTE;
	distanciaCavaRodaATras = DISTANCIA_CAVA_DA_RODA_A_TRAS;
	
	cor[0] = 0.1f;
	cor[1] = 0.3f;
	cor[2] = 0.15f;
	
	corJante[0] = coresJante[0];
	corJante[1] = coresJante[1];
	corJante[2] = coresJante[2];

	flagTexturas = true;

	pathTexturas = pathTex;

	initVariaveisDependentes();
	initRodas();
	initTextureFiles();
}

veiculo::veiculo(string pathTex, GLfloat cJante[3])
{
	ang_rot[0] = 0.0f;
	ang_rot[1] = 0.0f;
	ang_rot[2] = 0.0f;
	posicao.x = 0.0f;
	posicao.y = 0.0f;
	posicao.z = 0.0f;
	altura = ALTURA_VEICULO;
	largura = LARGURA_VEICULO;
	comprimento = COMPRIMENTO_VEICULO;
	raioEixo = RAIO_EIXO;
	distanciaCavaRodaAFrente = DISTANCIA_CAVA_DA_RODA_A_FRENTE;
	distanciaCavaRodaATras = DISTANCIA_CAVA_DA_RODA_A_TRAS;
	
	cor[0] = cJante[0];
	cor[1] = cJante[1];
	cor[2] = cJante[2];
	
	corJante[0] = cJante[0];
	corJante[1] = cJante[1];
	corJante[2] = cJante[2];

	flagTexturas = true;
	pathTexturas = pathTex;

	initVariaveisDependentes();
	initRodas();
	initTextureFiles();
}
veiculo::veiculo(GLfloat rotX, GLfloat rotY, GLfloat rotZ, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat Comprimento, GLfloat Largura, GLfloat Altura, GLfloat RaioEixo, GLfloat DistanciaCavaRodaAFrente, GLfloat DistanciaCavaRodaATras, string pathTex, GLfloat cores[3], GLfloat cJante[3])
{
	ang_rot[0] = rotX;
	ang_rot[1] = rotY;
	ang_rot[2] = rotZ;
	posicao.x = posX;
	posicao.y = posY;
	posicao.z = posZ;
	altura = Altura;
	largura = Largura;
	comprimento = Comprimento;
	raioEixo = RaioEixo;
	distanciaCavaRodaAFrente = DistanciaCavaRodaAFrente;
	distanciaCavaRodaATras = DistanciaCavaRodaATras;
	
	cor[0] = cores[0];
	cor[1] = cores[1];
	cor[2] = cores[2];

	corJante[0] = cJante[0];
	corJante[1] = cJante[1];
	corJante[2] = cJante[2];
	
	flagTexturas = true;

	pathTexturas = pathTex;
	
	initVariaveisDependentes();
	initRodas();
	initTextureFiles();
}

veiculo::~veiculo()
{
	for(int i = 0 ; i < 12 ; i++)
	{
		glDeleteLists(texturas[i].GetID(),1);
		texturas[i].~textura();
	}
}

void veiculo::initRodas()
{

	rodas.f_dir.setCor(corJante);
	rodas.f_dir.translacao((comprimento / 2.0) - distanciaCavaRodaAFrente - distanciaRodaAoChassis - rodas.f_dir.getRaioRoda(), 0.0f, largura/2.0 - rodas.t_dir.getLarguraPneu());
	rodas.f_esq.setCor(corJante);
	rodas.f_esq.translacao((comprimento / 2.0) - distanciaCavaRodaAFrente - distanciaRodaAoChassis - rodas.f_dir.getRaioRoda(), 0.0f, - largura/2.0 + rodas.t_dir.getLarguraPneu());
	rodas.f_esq.rotacao(0.0f, 180.0f,0.0f);
	rodas.t_dir.setCor(corJante);
	rodas.t_dir.translacao((-comprimento / 2.0) + distanciaCavaRodaATras + distanciaRodaAoChassis + rodas.f_dir.getRaioRoda(), 0.0f, largura/2.0 - rodas.t_dir.getLarguraPneu());
	rodas.t_esq.setCor(corJante);
	rodas.t_esq.translacao((-comprimento / 2.0) + distanciaCavaRodaATras + distanciaRodaAoChassis + rodas.f_dir.getRaioRoda(), 0.0f, - largura/2.0 + rodas.t_dir.getLarguraPneu());
	rodas.t_esq.rotacao(0.0f, 180.0f,0.0f);
	suplente.setCor(corJante);
}

void veiculo::initVariaveisDependentes()
{
	distanciaRodaAoChassis = rodas.f_dir.getRaioRoda() / 2.5f;
	distanciaEixoAoChassis = distanciaRodaAoChassis + rodas.f_dir.getRaioRoda();
	comprimentoCavaDaRoda = distanciaEixoAoChassis * 2.0f;
	larguraCavaDaRoda = rodas.f_dir.getLarguraPneu() * 2.0f;
	alturaCavaDaRoda = rodas.f_dir.getRaioRoda() * 1.2f;
	alturaCapot = altura / 8.0f;
	comprimentoCapot = distanciaCavaRodaAFrente + comprimentoCavaDaRoda;
	larguraTopoCapot = largura - (altura / 4.0f);
	comprimentoCabine = comprimento - distanciaCavaRodaAFrente - distanciaCavaRodaATras - (comprimentoCavaDaRoda * 2.0f) ;
	comprimentoCaixa = distanciaCavaRodaATras + comprimentoCavaDaRoda;
	this->flagATravar = false;
	this->flagAVirarParaADireita = false;
	this->flagAVirarParaAEsquerda = false;

	angPorta = 0.0f;
	
	for(int i = 0 ; i < 3 ; i++)
	{
		tremor[i] = 0.0f;
	}

	contaTranslacoes = 0;
	flagTexturesLoaded = false;
	if(Weather::activeWeather == Dia || Weather::activeWeather == Dia_Nevoeiro)
	{
		this->shininess[0] = 50.0f;
	}
	else
	{	
		this->shininess[0] = 0.0f;
	}
}

void veiculo::initDisplayLists()
{
	geraDLCarroceria();
}

void veiculo::initTextureFiles()
{
	texNames[0] = "frente.bmp";
	texNames[1] = "traseira_baixo.bmp";
	texNames[2] = "traseira_cima.bmp";
	texNames[3] = "capot.bmp";
	texNames[4] = "pixel_verde.bmp";
	texNames[5] = "capot_lado.bmp";
	texNames[6] = "lateral_tras_baixo.bmp";
	texNames[7] = "porta_baixo.bmp";
	texNames[8] = "pixel_verde_escuro.bmp";
	texNames[9] = "lateral_cima_tras.bmp";
	texNames[10] = "tejadilho.bmp";
	texNames[11] = "foco.bmp";
}

void veiculo::desenha()
{
	if(flagTexturesLoaded == false)
	{
		flagTexturesLoaded = true;
		loadTextures();
		initDisplayLists();
	}
	
	//animacao das rodas
	this->virarRodasParaEsquerda();
	this->virarRodasParaDireita();

	glPushMatrix();
		glTranslatef(posicao.x,posicao.y,posicao.z);
		glRotatef(-ang_rot[0] + tremor[0], 1.0f, 0.0f, 0.0f);
		glRotatef( ang_rot[1] + tremor[1], 0.0f, 1.0f, 0.0f);
		glRotatef( ang_rot[2] + tremor[2], 0.0f, 0.0f, 1.0f);
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -suplente.getRaioRoda());
			glRotatef(90.0f,1.0f,0.0f,0.0f);
			glRotatef(180.0f,0.0f,0.0f,1.0f);
			glPushMatrix();
				desenhaRodas();
			glPopMatrix();
			glPushMatrix();
				glCallList(this->dl_carroceria);
			glPopMatrix();		
		glPopMatrix();
	glPopMatrix();
}


void veiculo::viraAEsquerda()
{
	this->flagAVirarParaAEsquerda = true;
	if(this->flagAVirarParaADireita)
	{
		this->flagAVirarParaADireita = false;
	}
}

void veiculo::viraADireita()
{
	this->flagAVirarParaADireita = true;
	
	if(this->flagAVirarParaAEsquerda)
	{
		this->flagAVirarParaAEsquerda = false;
	}
}

void veiculo::vaiEmFrente()
{
	if(this->flagAVirarParaADireita)
	{
		this->flagAVirarParaADireita = false;
	}

	if(this->flagAVirarParaAEsquerda)
	{
		this->flagAVirarParaAEsquerda = false;
	}
}


void veiculo::virarRodasParaEsquerda()
{
	if(this->flagAVirarParaAEsquerda)
	{
		if(this->rodas.f_esq.getRotacaoY()- 180.0f < BRECAGEM_MAXIMA && this->rodas.f_dir.getRotacaoY() < BRECAGEM_MAXIMA)
		{
			this->rodas.f_esq.setRotacaoY(this->rodas.f_esq.getRotacaoY() + 5.0f);
			this->rodas.f_dir.setRotacaoY(this->rodas.f_dir.getRotacaoY() + 5.0f);
		}
	}
	else
	{
		if(this->rodas.f_esq.getRotacaoY() -180.0f > 0 && this->rodas.f_dir.getRotacaoY() > 0)
		{
			this->rodas.f_esq.setRotacaoY(this->rodas.f_esq.getRotacaoY() - 5.0f);
			this->rodas.f_dir.setRotacaoY(this->rodas.f_dir.getRotacaoY() - 5.0f);
		}
	}
}

void veiculo::virarRodasParaDireita()
{

	if(this->flagAVirarParaADireita)
	{
		if(this->rodas.f_esq.getRotacaoY() - 180.0f > -BRECAGEM_MAXIMA && this->rodas.f_dir.getRotacaoY() > -BRECAGEM_MAXIMA)
		{
			this->rodas.f_esq.setRotacaoY(this->rodas.f_esq.getRotacaoY() - 5.0f);
			this->rodas.f_dir.setRotacaoY(this->rodas.f_dir.getRotacaoY() - 5.0f);
		}
	}
	else
	{
		if(this->rodas.f_esq.getRotacaoY() - 180.0f < 0 && this->rodas.f_dir.getRotacaoY() < 0)
		{
			this->rodas.f_esq.setRotacaoY(this->rodas.f_esq.getRotacaoY() + 5.0f);
			this->rodas.f_dir.setRotacaoY(this->rodas.f_dir.getRotacaoY() + 5.0f);
		}
	}
}


//vira a roda direita de acordo com o angulo recebido do ODE
//nao está a ser utilizado
void veiculo::virarRodaDireita(GLfloat ang_y)
{
	rodas.f_dir.setRotacaoY(ang_y);
}
//vira a roda esquerda de acordo com o angulo recebido do ODE
//nao está a ser utilizado
void veiculo::virarRodaEsquerda(GLfloat ang_y)
{
	rodas.f_esq.setRotacaoY(ang_y);
}

void veiculo::rotacaoRodas(GLfloat ang_z)
{
	rodas.f_esq.setRotacaoZ(rodas.f_esq.getRotacaoZ() + ang_z);
	rodas.t_dir.setRotacaoZ(rodas.t_dir.getRotacaoZ() - ang_z);
	rodas.f_dir.setRotacaoZ(rodas.f_dir.getRotacaoZ() - ang_z);
	rodas.t_esq.setRotacaoZ(rodas.t_esq.getRotacaoZ() + ang_z);
}

void veiculo::criaSocalco()
{
	contaTranslacoes++;
	int i;

	if(contaTranslacoes % 3 == 0)
	{
		if(contaTranslacoes % 10 == 0)
		{		
			for(i = 0 ; i < 3 ; i++)
			{
				tremor[i] = (rand() % 6) - 3;
			}
		}
		if(contaTranslacoes % 7 == 0)
		{		
			for(i = 0 ; i < 3 ; i++)
			{
				tremor[i] -= 1;
			}
		}
		if(contaTranslacoes % 4 == 0)
		{		
			for(i = 0 ; i < 3 ; i++)
			{
				tremor[i] += 1;
			}
		}
	}
}

void veiculo::mover(GLfloat x, GLfloat y, GLfloat z)
{
	posicao.x += x;
	posicao.y += y;
	posicao.z += z;
}

void veiculo::switchTexturasOnOff()
{
	if(flagTexturas)
		flagTexturas = false;
	else
		flagTexturas = true;
}

void veiculo::poeARodar()
{
	ang_rot[2] -= 2.0f;
}

void veiculo::pressionaTravao()
{
	if(!this->flagATravar)
	{
		this->flagATravar = true;
	}		
}

void veiculo::soltaTravao()
{
	if(this->flagATravar)
	{
		this->flagATravar = false;
	}		
}
//-------------------------------
//Métodos de desenho do veículo
//-------------------------------
void veiculo::desenhaRodas()
{
	glPushMatrix();
		rodas.f_esq.desenha();
	glPopMatrix();
	glPushMatrix();
		rodas.f_dir.desenha();
	glPopMatrix();
	glPushMatrix();
		rodas.t_esq.desenha();
	glPopMatrix();
	glPushMatrix();
		rodas.t_dir.desenha();
	glPopMatrix();
}
void veiculo::desenhaEixos()
{
	glColor3f(0.2f, 0.2f, 0.2f);
	//eixo da frente
	glPushMatrix();
		glTranslatef((comprimento / 2.0) - distanciaCavaRodaAFrente - (comprimentoCavaDaRoda / 2.0),0.0f,0.0f);
		geraPoligono::esfera(raioEixo * 5.0, 10.0, 10.0);
		glTranslatef(0.0f, 0.0f, -(largura / 2.0) + rodas.t_dir.getLarguraPneu());
		geraPoligono::cilindroFechado(1.0f,raioEixo,largura - (rodas.t_dir.getLarguraPneu() * 2.0),6.0f,1.0f);	
	glPopMatrix();
	
	//eixo de tras
	glPushMatrix();
		glTranslatef((-comprimento / 2.0) + distanciaCavaRodaATras + (comprimentoCavaDaRoda / 2.0),0.0f,0.0f);
		geraPoligono::esfera(raioEixo * 5.0, 10.0, 10.0);
		glTranslatef(0.0f,0.0f,-(largura / 2.0) + rodas.t_dir.getLarguraPneu());
		geraPoligono::cilindroFechado(1.0f,raioEixo,largura - (rodas.t_dir.getLarguraPneu() * 2.0),6.0f,1.0f);	
	glPopMatrix();
	glColor3f(cor[0], cor[1], cor[2]);
}

void veiculo::desenhaCarroceria()
{
	//desenhar a parte de baixo do carro
	desenhaFundo();
	desenhaMeio();
	desenhaTopo();
}

void veiculo::desenhaFundo()
{
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[8].SetActive();
	}
	glPushMatrix();
		//parte de baixo
		glRotatef(-90.0f,1.0f,0.0f,0.0f);
		//atras do eixo de traz
		glRectf(-comprimento / 2.0, -largura / 2.0, -comprimento / 2.0 + distanciaCavaRodaATras, largura / 2.0);
		//entre as rodas de tras a vermelho
		glRectf((-comprimento / 2.0) + distanciaCavaRodaATras, (-largura / 2.0) + larguraCavaDaRoda , (-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, (largura / 2.0) - larguraCavaDaRoda);
		//no meio do veiculo a amarelo
		glRectf((-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, - largura / 2.0, (comprimento / 2.0) - comprimentoCavaDaRoda - distanciaCavaRodaAFrente, largura/2.0);
		//entre as rodas da frente a salmão
		glRectf((comprimento / 2.0) - comprimentoCavaDaRoda - distanciaCavaRodaAFrente, (-largura / 2.0) + larguraCavaDaRoda, (comprimento / 2.0) - distanciaCavaRodaAFrente, (largura / 2.0) - larguraCavaDaRoda);
		//parte da frente a rosa
		glRectf((comprimento / 2.0)  - distanciaCavaRodaAFrente, (-largura / 2.0), (comprimento / 2.0), (largura / 2.0));
	glPopMatrix();
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
}

void veiculo::desenhaMeio()
{
	
	glPushMatrix();
		glTranslatef(0.0f,0.0f,(largura/2.0));
		//desenha lado esquerdo ate meio
		glPushMatrix();
			//painel tras
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[6].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f((-comprimento / 2.0f), 0.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f((-comprimento / 2.0) + distanciaCavaRodaATras, 0.0f, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f((-comprimento / 2.0) + distanciaCavaRodaATras, altura / 2.0f, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f((-comprimento / 2.0f), altura / 2.0f, 0.0f);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//glRectf((-comprimento / 2.0f), 0.0f ,(-comprimento / 2.0) + distanciaCavaRodaATras, altura / 2.0f);
			//painel cima roda de tras
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[4].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda, 0.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda, 0.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura * 0.5f, 0.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras, altura * 0.5f, 0.0f);
			glEnd();
			//glRectf((-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda ,(-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura/2.0);
			geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda, 0.0f, 0.0f, 1.0f);
			geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras + (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda, 0.0f, 0.0f, 1.0f);
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//painel do meio
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[7].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, 0.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, 0.0f, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura / 2.0f, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura / 2.0f, 0.0f);
			glEnd();	
			//glRectf((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, 0.0f ,(comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura/2.0);
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[4].SetActive();
			}
			//painel cima roda frente
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda, 0.0f);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente , alturaCavaDaRoda, 0.0f);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente , altura / 2.0f, 0.0f);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura/2.0, 0.0f) ;
			glEnd();
			//glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda ,(comprimento / 2.0f) - distanciaCavaRodaAFrente , altura/2.0);
			geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente, alturaCavaDaRoda / 2.0f, (comprimento / 2.0f) - distanciaCavaRodaAFrente, alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda, 0.0f, 0.0f, 1.0f);
			geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (comprimento / 2.0) - distanciaCavaRodaAFrente - (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda, 0.0f, 0.0f, 1.0f);
			//painel frente direita
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente, 0.0f, 0.0f);
				glVertex3f((comprimento / 2.0f) , 0.0f, 0.0f);
				glVertex3f((comprimento / 2.0f) , altura/2.0, 0.0f);
				glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente, altura/2.0, 0.0f) ;
			glEnd();
			//glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente, 0.0f ,(comprimento / 2.0f), altura / 2.0f);
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
		glPopMatrix();
	glPopMatrix();
	//desenha lado direito até meio
	glPushMatrix();
		glTranslatef(0.0f,0.0f,(-largura/2.0));
		//painel tras
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[6].SetActive();
		}
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0,0.0);
			glVertex3f((-comprimento / 2.0f), 0.0f, 0.0f);
			glTexCoord2f(1.0,0.0);
			glVertex3f((-comprimento / 2.0) + distanciaCavaRodaATras, 0.0f, 0.0f);
			glTexCoord2f(1.0,1.0);
			glVertex3f((-comprimento / 2.0) + distanciaCavaRodaATras, altura / 2.0f, 0.0f);
			glTexCoord2f(0.0,1.0);
			glVertex3f((-comprimento / 2.0f), altura / 2.0f, 0.0f);
		glEnd();
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		//glRectf((-comprimento / 2.0f), 0.0f ,(-comprimento / 2.0) + distanciaCavaRodaATras, altura / 2.0f);
		//painel cima roda de tras
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[4].SetActive();
		}
		glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda, 0.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda, 0.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura * 0.5f, 0.0f);
				glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras, altura * 0.5f, 0.0f);
			glEnd();
		//glRectf((-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda ,(-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura/2.0);
		geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda, 0.0f, 0.0f, -1.0f);
		geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras + (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda, 0.0f, 0.0f, -1.0f);
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		//painel do meio
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[7].SetActive();
		}
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0,0.0);
			glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, 0.0f, 0.0f);
			glTexCoord2f(1.0,0.0);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, 0.0f, 0.0f);
			glTexCoord2f(1.0,1.0);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura / 2.0f, 0.0f);
			glTexCoord2f(0.0,1.0);
			glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura / 2.0f, 0.0f);
		glEnd();	
		//glRectf((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, 0.0f ,(comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura/2.0);
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[4].SetActive();
		}
		//painel cima roda frente
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda, 0.0f);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente , alturaCavaDaRoda, 0.0f);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente , altura/2.0, 0.0f);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura/2.0, 0.0f) ;
		glEnd();
		//glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda ,(comprimento / 2.0f) - distanciaCavaRodaAFrente , altura/2.0);
		geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente, alturaCavaDaRoda / 2.0f, (comprimento / 2.0f) - distanciaCavaRodaAFrente, alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda, 0.0f, 0.0f, -1.0f);
		geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (comprimento / 2.0) - distanciaCavaRodaAFrente - (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda, 0.0f, 0.0f, -1.0f);
		//painel frente direita
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente, 0.0f, 0.0f);
			glVertex3f((comprimento / 2.0f) , 0.0f, 0.0f);
			glVertex3f((comprimento / 2.0f) , altura/2.0, 0.0f);
			glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente, altura/2.0, 0.0f) ;
		glEnd();
		//glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente, 0.0f ,(comprimento / 2.0f), altura / 2.0f);
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		//desenhaPainelLateralCentral();
	glPopMatrix();
	
	//PARA APAGAR ESTA LINHA
	//display_list_cava_da_roda = geraDLCavaDaRoda();
	glPushMatrix();
		desenhaCavasDasRodas();
	glPopMatrix();
	//desenha a frente do carro ate metade
	desenhaFrenteAteMeio();
	//desenha a traseira do carro até meio
	desenhaTraseiraAteMeio();
}
/*void veiculo::desenhaPainelLateralCentral()
{
	//painel tras
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[6].SetActive();
	}
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0,0.0);
		glVertex3f((-comprimento / 2.0f), 0.0f, 0.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f((-comprimento / 2.0) + distanciaCavaRodaATras, 0.0f, 0.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f((-comprimento / 2.0) + distanciaCavaRodaATras, altura / 2.0f, 0.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f((-comprimento / 2.0f), altura / 2.0f, 0.0f);
	glEnd();
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
	//glRectf((-comprimento / 2.0f), 0.0f ,(-comprimento / 2.0) + distanciaCavaRodaATras, altura / 2.0f);
	//painel cima roda de tras
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[4].SetActive();
	}
	glRectf((-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda ,(-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura/2.0);
	//geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda, 0.0f, 0.0f, 1.0f);
	//geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras + (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda, 0.0f, 0.0f, 1.0f);
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
	//painel do meio
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[7].SetActive();
	}
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0,0.0);
		glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, 0.0f, 0.0f);
		glTexCoord2f(1.0,0.0);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, 0.0f, 0.0f);
		glTexCoord2f(1.0,1.0);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura / 2.0f, 0.0f);
		glTexCoord2f(0.0,1.0);
		glVertex3f((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, altura / 2.0f, 0.0f);
	glEnd();	
	//glRectf((-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda, 0.0f ,(comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura/2.0);
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[4].SetActive();
	}
	//painel cima roda frente
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda, 0.0f);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente , alturaCavaDaRoda, 0.0f);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente , altura/2.0, 0.0f);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, altura/2.0, 0.0f) ;
	glEnd();
	//glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda ,(comprimento / 2.0f) - distanciaCavaRodaAFrente , altura/2.0);
	//geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente, alturaCavaDaRoda / 2.0f, (comprimento / 2.0f) - distanciaCavaRodaAFrente, alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda);
	//geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (comprimento / 2.0) - distanciaCavaRodaAFrente - (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda);
	//painel frente direita
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente, 0.0f, 0.0f);
		glVertex3f((comprimento / 2.0f) , 0.0f, 0.0f);
		glVertex3f((comprimento / 2.0f) , altura/2.0, 0.0f);
		glVertex3f((comprimento / 2.0f) - distanciaCavaRodaAFrente, altura/2.0, 0.0f) ;
	glEnd();
	//glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente, 0.0f ,(comprimento / 2.0f), altura / 2.0f);
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
}*/

void veiculo::desenhaCavasDasRodas()
{
	//desenha cava todas as cavas das rodas
	glPushMatrix();
		glTranslatef((-comprimento / 2.0) + distanciaCavaRodaATras,0.0f,(largura / 2.0) - larguraCavaDaRoda);
		desenhaCavaDaRoda(1.0f);
	glPopMatrix();
	//frente direita
	glPushMatrix();
		glTranslatef((comprimento / 2.0) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda,0.0f,(largura / 2.0) - larguraCavaDaRoda);
		desenhaCavaDaRoda(1.0f);
	glPopMatrix();
	//tras esquerda
	glPushMatrix();
		glTranslatef((-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda,0.0f,-(largura / 2.0) + larguraCavaDaRoda);
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		desenhaCavaDaRoda(1.0f);
	glPopMatrix();
	//frente esquerda
	glPushMatrix();
		glTranslatef((comprimento / 2.0) - distanciaCavaRodaAFrente,0.0f,-(largura / 2.0) + larguraCavaDaRoda);
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		desenhaCavaDaRoda(1.0f);
	glPopMatrix();
}

void veiculo::desenhaCavaDaRoda(GLfloat x)
{	
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[8].SetActive();
	}
	glPushMatrix();
		glRotatef(-90.0f,0.0f,1.0f,0.0f);
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, x * -1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f); 
			glVertex3f(larguraCavaDaRoda, 0.0f, 0.0f);
			glVertex3f(larguraCavaDaRoda,alturaCavaDaRoda, 0.0f);
			glVertex3f(0.0f, alturaCavaDaRoda, 0.0f);
		glEnd();
		//glRectf(0.0f,0.0f,larguraCavaDaRoda,alturaCavaDaRoda);
	glPopMatrix();
	//parte de cima
	glPushMatrix();
		glTranslatef(0.0f,alturaCavaDaRoda,larguraCavaDaRoda);
		glRotatef(-90.0f,1.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f); 
			glVertex3f(comprimentoCavaDaRoda, 0.0f, 0.0f);
			glVertex3f(comprimentoCavaDaRoda,larguraCavaDaRoda, 0.0f);
			glVertex3f(0.0f, larguraCavaDaRoda, 0.0f);
		glEnd();
		//glRectf(0.0f,0.0f,comprimentoCavaDaRoda,larguraCavaDaRoda);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(comprimentoCavaDaRoda,0.0f,0.0f);
		glRotatef(-90.0f,0.0f,1.0f,0.0f);
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, x * 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f); 
			glVertex3f(larguraCavaDaRoda, 0.0f, 0.0f);
			glVertex3f(larguraCavaDaRoda,alturaCavaDaRoda, 0.0f);
			glVertex3f(0.0f, alturaCavaDaRoda, 0.0f);
		glEnd();
		//glRectf(0.0f,0.0f,larguraCavaDaRoda,alturaCavaDaRoda);
	glPopMatrix();
	//parte de dentro
	glPushMatrix();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, x * 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f); 
			glVertex3f(comprimentoCavaDaRoda, 0.0f, 0.0f);
			glVertex3f(comprimentoCavaDaRoda,alturaCavaDaRoda, 0.0f);
			glVertex3f(0.0f, alturaCavaDaRoda, 0.0f);
		glEnd();	
		//glRectf(0.0f,0.0f,comprimentoCavaDaRoda,alturaCavaDaRoda);
	glPopMatrix();
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
}

void veiculo::desenhaFrenteAteMeio()
{
	glPushMatrix();
		glTranslatef(comprimento * 0.5f, 0.0f,-largura * 0.5f);
		glRotatef(-90.0f,0.0f,1.0f,0.0f);
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[0].SetActive();
		}
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0,0.0);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0,0.0);
			glVertex3f(largura, 0.0f, 0.0f);
			glTexCoord2f(1.0,1.0);
			glVertex3f(largura,altura * 0.5f, 0.0f);
			glTexCoord2f(0.0,1.0);
			glVertex3f(0.0f, altura * 0.5f, 0.0f);
		glEnd();
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		//glRectf(0.0f,0.0f,largura,altura/2.0);
		//farol frente esquerda
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			glEnable (GL_BLEND); 
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glTranslatef(largura * 0.150f, altura * 0.5f - largura * 0.125f, -comprimento * 0.02f);
			geraPoligono::cilindroFechado(1.0f, largura * 0.10f, comprimento * 0.01f, 10.0f, 1.0f);
		glPopMatrix();
		//farol frente direita
		glPushMatrix();
			glTranslatef(largura * 0.850f , altura * 0.5f - largura * 0.125f, -comprimento * 0.02f);
			geraPoligono::cilindroFechado(1.0f, largura * 0.10f, comprimento * 0.01f, 10.0f, 1.0f);
			glDisable(GL_BLEND);
		glPopMatrix();
	glPopMatrix();
	glColor3f(cor[0], cor[1], cor[2]);
}

void veiculo::desenhaTraseiraAteMeio()
{
	glPushMatrix();
		glTranslatef(-comprimento / 2.0,0.0f,-largura / 2.0);
		glRotatef(-90.0f,0.0f,1.0f,0.0f);
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[1].SetActive();
		}
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glTexCoord2f(1.0,0.0);
			glVertex3f(largura, 0.0f, 0.0f);
			glTexCoord2f(1.0,1.0);
			glVertex3f(largura,altura / 2.0f, 0.0f);
			glTexCoord2f(0.0,1.0);
			glVertex3f(0.0f, altura / 2.0f, 0.0f);
		glEnd();
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		//glRectf(0.0f,0.0f,largura,altura/2.0);
	glPopMatrix();
	desenhaStops();
}

void veiculo::desenhaTopo()
{
	glPushMatrix();
		desenhaCapot();
	glPopMatrix();
	glPushMatrix();
		desenhaCabine();
	glPopMatrix();
	glPushMatrix();
		desenhaCaixa();
	glPopMatrix();
}

void veiculo::desenhaCapot()
{
	GLfloat x = ((largura - larguraTopoCapot) / 2.0f);
	GLfloat y = ((alturaCapot));
	GLfloat lPaineisInclinados = sqrt((x * x) + (y * y));

	glPushMatrix();
		glTranslatef(0.0f, (altura / 2.0f), 0.0f);
		//desenho do topo do capot
		glPushMatrix();
			glTranslatef((comprimento / 2.0f) - comprimentoCapot, alturaCapot, -(largura / 2.0f) + x);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[3].SetActive();
			}//desenho do capot
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(comprimentoCapot, 0.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(comprimentoCapot, larguraTopoCapot, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(0.0f, larguraTopoCapot, 0.0f);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//glRectf(0.0f, 0.0f, comprimentoCapot, larguraTopoCapot);
		glPopMatrix();
		//desenho do painel lateral esquerda
		glPushMatrix();
			glTranslatef((comprimento / 2.0) - comprimentoCapot, 0.0f, largura / 2.0f);
			glRotatef(-45, 1.0f, 0.0f, 0.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[5].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(comprimentoCapot, 0.0f, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(comprimentoCapot, lPaineisInclinados, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(0.0f, lPaineisInclinados, 0.0f);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//glRectf(0.0f, 0.0f, comprimentoCapot, lPaineisInclinados);
		glPopMatrix();
		//desenho do painel lateral direita
		glPushMatrix();
			glTranslatef((comprimento / 2.0) - comprimentoCapot, 0.0f, -largura / 2.0f);
			glRotatef(45, 1.0f, 0.0f, 0.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[5].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(comprimentoCapot, 0.0f, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(comprimentoCapot, lPaineisInclinados, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(0.0f, lPaineisInclinados, 0.0f);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//glRectf(0.0f, 0.0f, comprimentoCapot, lPaineisInclinados);
		glPopMatrix();
		//desenho da frente do capot
		glPushMatrix();
			glTranslatef((comprimento / 2.0),0.0f,-(largura / 2.0f));
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			glRotatef(90, 0.0f, 0.0f, 1.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[4].SetActive();
			}//textura da traseira(parte de cima)
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex2f(0.0f, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex2f(0.0f, largura);
				glTexCoord2f(1.0,1.0);
				glVertex2f(alturaCapot, x + larguraTopoCapot);
				glTexCoord2f(1.0,0.0);
				glVertex2f(alturaCapot, x);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
		glPopMatrix();
	glPopMatrix();
}

void veiculo::desenhaCabine()
{
	GLfloat deslocamento;
	
	//este deslocamento é necessário calcular devido ás distancias das cavas da frente e de tras poderem ser diferentes
	deslocamento = -((distanciaCavaRodaAFrente - distanciaCavaRodaATras) / 2.0f);
	
	glPushMatrix();		
		glTranslatef(deslocamento, (altura / 2.0f), 0.0f);
		//desenha a barra frontal da cabine
		glPushMatrix();
			glTranslatef(comprimentoCabine / 2.0f, 0.0f, largura / 2.0f);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[4].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(largura, 0.0f, 0.0f);
				glVertex3f(largura, alturaCapot, 0.0f);
				glVertex3f(0.0f, alturaCapot, 0.0f);
			glEnd();			
			//glRectf(0.0f,0.0f,largura, alturaCapot);
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
		glPopMatrix();
		//desenha a janela do lado esquerdo
		glPushMatrix();
			desenhaJanelaCabine(1.0f);
		glPopMatrix();
		//desenha o para brisas
		glPushMatrix();
			desenhaParaBrisas();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(comprimentoCabine * 0.35 , -(altura / 2.0f), -(largura / 2.0f) + (larguraCavaDaRoda / 2.0f));
			desenhaBanco();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(comprimentoCabine * 0.35, -(altura / 2.0f), larguraCavaDaRoda / 2.0f);
			desenhaBanco();
		glPopMatrix();
		//desenha a janela do lado direito
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -largura);
			desenhaJanelaCabine(-1.0f);
		glPopMatrix();
		//bara superior da cabine
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[4].SetActive();
		}
		glPushMatrix();
			glTranslatef(-(comprimentoCabine / 2.0f), altura / 2.0f, largura / 2.0f);
			glRotatef(90, 0.0f, 1.0f, 0.0f);
			glRotatef(90, 1.0f, 0.0f, 0.0f);
			glRectf(0.0f, 0.0f, largura, comprimentoCabine * 0.1f);
		glPopMatrix();
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		glPushMatrix();
			desenhaBarraCFocos();
		glPopMatrix();
	glPopMatrix();
}


void veiculo::desenhaJanelaCabine(GLfloat x)
{
	glPushMatrix();
			glTranslatef(-comprimentoCabine / 2.0, 0.0f, (largura / 2.0));
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[4].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, x * 1.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(comprimentoCabine, 0.0f, 0.0f);
				glVertex3f(comprimentoCabine, alturaCapot, 0.0f);
				glVertex3f(0.0f, alturaCapot, 0.0f);
			glEnd();
			
			//glRectf(0.0f,0.0f,comprimentoCabine,alturaCapot);
			glPushMatrix();
				glTranslatef(0.0f, alturaCapot, 0.0f);
				//friso de tras do vidro
				glBegin(GL_QUADS);
					glNormal3f(0.0f, 0.0f, x * 1.0f);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f((comprimentoCabine)* 0.1, 0.0f, 0.0f);
					glVertex3f((comprimentoCabine)* 0.1, (altura / 2.0f) - alturaCapot, 0.0f);
					glVertex3f(0.0f,(altura / 2.0f) - alturaCapot, 0.0f);
				glEnd();
				//glRectf(0.0f, 0.0f, (comprimentoCabine)* 0.1, (altura / 2.0f) - alturaCapot);
				glTranslatef((comprimentoCabine * 0.1f), 0.0f, 0.0f);
				//friso da frente do vidro
				glBegin(GL_QUADS);
					glNormal3f(0.0f, 0.0f, x * 1.0f);
					glVertex2f(0.0f, ((altura / 2.0f)) - alturaCapot);
					glVertex2f(0.0f, ((altura / 2.0f) * 0.9f) - alturaCapot);
					glVertex2f(comprimentoCabine * 0.8f, 0.0f);
					glVertex2f(comprimentoCabine * 0.9f, 0.0f);
				glEnd();
				if(flagTexturas)
				{
					glDisable(GL_TEXTURE_2D);
				}
				//janela
				glColor4f(0.0f,0.0f,1.0f,0.5f);
				GLfloat mat_amb_diff[] = { 0.0, 0.0, 0.5, 1.0 };
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
				glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				geraPoligono::triangulo(0.0f, 0.0f, comprimentoCabine * 0.8f, 0.0f, 0.0f, ((altura / 2.0f) * 0.9f) - alturaCapot, 0.0f, 0.0f, x * 1.0f);
				glDisable(GL_BLEND);
				glColor3f(cor[0], cor[1], cor[2]);
				GLfloat mat_amb_diff2[] = { 1.0, 1.0, 1.0, 1.0 };
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff2);
			glPopMatrix();
		glPopMatrix();
}

void veiculo::desenhaParaBrisas()
{
	GLfloat x = comprimentoCabine * 0.9f;
	GLfloat y = ((altura) / 2.0f ) - alturaCapot;
	GLfloat alturaParaBrisas = sqrt((x * x) + (y * y));
	
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[4].SetActive();
	}
	glTranslatef(comprimentoCabine / 2.0, alturaCapot, -(largura / 2));
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef((180 * atan(x/y)) / PI, 1.0f, 0.0f, 0.0f);
	//friso inferior
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(largura, 0.0f, 0.0f);
		glVertex3f(largura, alturaParaBrisas * 0.1f, 0.0f);
		glVertex3f(0.0f, alturaParaBrisas * 0.1f, 0.0f);
	glEnd();
	//glRectf(0.0f, 0.0f, largura, alturaParaBrisas * 0.1f);
	//friso da esquerda
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, alturaParaBrisas * 0.1f, 0.0f);
		glVertex3f(largura * 0.05f, alturaParaBrisas * 0.1f, 0.0f);
		glVertex3f(largura * 0.05f, alturaParaBrisas * 0.9f, 0.0f);
		glVertex3f(0.0f, alturaParaBrisas * 0.9f, 0.0f);
	glEnd();	
	//glRectf(0.0f, alturaParaBrisas * 0.1f, largura * 0.05f, alturaParaBrisas * 0.9f);
	//friso da direita
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(largura * 0.95f, alturaParaBrisas * 0.1f, 0.0f);
		glVertex3f(largura, alturaParaBrisas * 0.1f, 0.0f);
		glVertex3f(largura, alturaParaBrisas * 0.9f, 0.0f);
		glVertex3f(largura * 0.95f, alturaParaBrisas * 0.9f, 0.0f);
	glEnd();	
	//glRectf(largura * 0.95f, alturaParaBrisas * 0.1f, largura, alturaParaBrisas * 0.9f);
	//friso superior
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, alturaParaBrisas * 0.9f, 0.0f);
		glVertex3f(largura, alturaParaBrisas * 0.9f, 0.0f);
		glVertex3f(largura, alturaParaBrisas, 0.0f);
		glVertex3f(0.0f, alturaParaBrisas, 0.0f);
	glEnd();
	//glRectf(0.0f, alturaParaBrisas * 0.9f, largura, alturaParaBrisas);
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
	//janela
	GLfloat mat_amb_diff[] = { 0.0, 0.0, 0.5, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
	glColor4f(0.0f,0.0f,1.0f,0.5f);
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(largura * 0.05f, alturaParaBrisas * 0.1f, 0.0f);
		glVertex3f(largura * 0.95f, alturaParaBrisas * 0.1f, 0.0f);
		glVertex3f(largura * 0.95f, alturaParaBrisas * 0.9f, 0.0f);
		glVertex3f(largura * 0.05f, alturaParaBrisas * 0.9f, 0.0f);
	glEnd();
	//glRectf(largura * 0.05f, alturaParaBrisas * 0.1f, largura * 0.95f, alturaParaBrisas * 0.9f);
	glDisable(GL_BLEND);
	glColor3f(cor[0], cor[1], cor[2]);
	GLfloat mat_amb_diff2[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff2);
}

void veiculo::desenhaCaixa()
{
	glColor3f(cor[0], cor[1]- 0.1f, cor[2]);
	//painel do lado direito
	glPushMatrix();
		glTranslatef(0.0f, altura / 2.0f, 0.0f);
		glPushMatrix();
			glTranslatef(-(comprimento / 2.0f), 0.0f, (largura / 2.0f));
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[9].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(0.0f, altura / 2.0f, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(comprimentoCaixa,altura / 2.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(comprimentoCaixa, 0.0f, 0.0f);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			glRectf(0.0f, 0.0f, comprimentoCaixa, altura / 2.0f);
		glPopMatrix();
		//painel da traseira
		glPushMatrix();
			glTranslatef(-(comprimento / 2.0f), 0.0f, -(largura / 2.0f));
			glRotatef(-90.0f,0.0f,1.0f,0.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[2].SetActive();
			}//textura da traseira(parte de cima)
				glBegin(GL_QUADS);
					glNormal3f(0.0f, 0.0f, 1.0f);
					glTexCoord2f(0.0,0.0);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glTexCoord2f(1.0,0.0);
					glVertex3f(largura, 0.0f, 0.0f);
					glTexCoord2f(1.0,1.0);
					glVertex3f(largura,altura / 2.0f, 0.0f);
					glTexCoord2f(0.0,1.0);
					glVertex3f(0.0f, altura / 2.0f, 0.0f);
				glEnd();
				if(flagTexturas)
				{
					glDisable(GL_TEXTURE_2D);
				}
			//glRectf(0.0f, 0.0f, largura, altura / 2.0f);
		glPopMatrix();
		//painel do lado esquerdo
		glPushMatrix();
			glTranslatef(-(comprimento / 2.0f), 0.0f, -(largura / 2.0f));
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[9].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, -1.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(0.0f, altura / 2.0f, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(comprimentoCaixa,altura / 2.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(comprimentoCaixa, 0.0f, 0.0f);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//glRectf(0.0f, 0.0f, comprimentoCaixa, altura / 2.0f);
		glPopMatrix();
		//tejadilho
		glPushMatrix();
			glTranslatef(-(comprimento / 2.0f), altura / 2.0f, -(largura / 2.0f));
			glRotatef(90.0f,1.0f,0.0f,0.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[10].SetActive();
			}
			glBegin(GL_QUADS);
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0,0.0);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(0.0,1.0);
				glVertex3f(comprimentoCaixa, 0.0f, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex3f(comprimentoCaixa, largura, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex3f(0.0f, largura, 0.0f);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			//glRectf(0.0f, 0.0f, comprimentoCaixa, largura);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-(comprimento / 2.0f), 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
			glPushMatrix();
				suplente.desenha();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glColor3f(cor[0], cor[1], cor[2]);

}


void veiculo::desenhaBanco()
{
	GLdouble comprimentoBanco = comprimentoCabine * 1.0f;
	GLdouble larguraBanco = largura / 3.0f;
	GLdouble alturaBanco = altura / 6.0f;
	GLdouble alturaEncosto = altura  * 0.6f;
	GLdouble espessuraEncosto = comprimentoBanco / 4.0f;
	
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		geraPoligono::cubo(larguraBanco,comprimentoBanco, alturaBanco);
		glPushMatrix();
			glTranslatef(comprimentoBanco, alturaBanco, 0.0);
			glRotatef(80.0f, 0.0f, 0.0f, 1.0f);
			geraPoligono::cubo(larguraBanco, alturaEncosto, espessuraEncosto);
		glPopMatrix();
	glPopMatrix();
	glColor3f(cor[0], cor[1], cor[2]);
}

void veiculo::desenhaBarraCFocos()
{
	/*GLfloat LuzAmbiente []={0.2,0.2,0.2,1.0};
	GLfloat LuzDifusa []={1.0,1.0,1.0,1.0};
	GLfloat LuzEspecular []={1.0,1.0,1.0,1.0};
	GLfloat LuzPosicao []={-this->comprimento , this->altura, 0.0f, 1.0};
	GLfloat LuzDireccao []={1.0f, 0.0f, 0.0f, 0.0f};*/

	GLfloat LuzAmbiente []={0.2,0.2,0.2,1.0};
	GLfloat LuzDifusa []={1.0,1.0,1.0,1.0};
	GLfloat LuzEspecular []={1.0,1.0,1.0,1.0};
	GLfloat LuzPosicao []={-0.5,0.0,0.0,1.0};
	GLfloat LuzDireccao []={1.0f, 0.0f, 0.0f, 0.0f};

	if(Weather::activeWeather == Noite || Weather::activeWeather == Noite_Nevoeiro)
	{
		//glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1,GL_AMBIENT,LuzAmbiente);
		glLightfv(GL_LIGHT1,GL_DIFFUSE,LuzDifusa);
		glLightfv(GL_LIGHT1,GL_SPECULAR,LuzEspecular);
		glLightfv(GL_LIGHT1,GL_POSITION,LuzPosicao);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.005);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.01);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.01);
		glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,25.0f);
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,LuzDireccao);
	}

	glPushMatrix();
		glTranslatef(-comprimentoCabine / 2.0f, altura / 2.0f, largura / 2.0f);
		if(flagTexturas)
		{
			glEnable(GL_TEXTURE_2D);
			texturas[6].SetActive();
		}
		geraPoligono::cubo(largura, largura / 24.0f, largura / 24.0f);
		if(flagTexturas)
		{
			glDisable(GL_TEXTURE_2D);
		}
		glPushMatrix();
			glTranslatef(largura / 24.0f, largura / 24.0f, -largura / 16.0f);
			glPushMatrix();
				desenhaFoco();
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, -largura / 4.0f);
				desenhaFoco();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -largura * 0.5f);
				desenhaFoco();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, - 0.75 * largura);
				desenhaFoco();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void veiculo::desenhaFoco()
{
	GLfloat larguraFoco = largura / 8.0f;
	GLfloat alturaFoco = larguraFoco * (2.0f /3.0f);
	GLfloat profundidadeFoco = alturaFoco / 2.0f;
	
	GLfloat mat_amb_diff[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_amb_diff_temp[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_shininess_temp[] = { 100.0 };

	glPushMatrix();
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[11].SetActive();
			}
			glBegin(GL_QUADS);
				glTexCoord2f(0.0,0.0);
				glVertex2f(0.0f, 0.0f);
				glTexCoord2f(1.0,0.0);
				glVertex2f(larguraFoco, 0.0f);
				glTexCoord2f(1.0,1.0);
				glVertex2f(larguraFoco, alturaFoco);
				glTexCoord2f(0.0,1.0);
				glVertex2f(0.0f, alturaFoco);
			glEnd();
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
			
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff_temp);
			glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_temp);
			
			glColor3f(0.0f, 0.0f, 0.0f);
			glTranslatef(0.0f,0.0f, -profundidadeFoco);
			glRectf(0.0f, 0.0f, larguraFoco, alturaFoco);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0f,0.0f, -profundidadeFoco);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glPushMatrix();
				glPushMatrix();
					glTranslatef(0.0f, 0.0f, -alturaFoco);
					glRectf(0.0f, 0.0f, larguraFoco, profundidadeFoco);
				glPopMatrix();
				glPushMatrix();
					glRectf(0.0f, 0.0f, larguraFoco, profundidadeFoco);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glRectf(0.0f,0.0f, profundidadeFoco, alturaFoco);
			glTranslatef(0.0f, 0.0f, larguraFoco);
			glRectf(0.0f,0.0f, profundidadeFoco, alturaFoco);
		glPopMatrix();
	glPopMatrix();
	glColor3f(cor[0], cor[1], cor[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
	glMaterialfv(GL_FRONT, GL_SHININESS, this->shininess);
}


void veiculo::desenhaStops()
{
	GLfloat mat_amb_diff[] = { 8.0, 0.0, 0.0, 1.0 };
	GLfloat mat_amb_shininess[] = { 100.0 };//brilho maximo qd o travao estiver activo
	GLfloat mat_amb_diff2[] = { 1.0, 1.0, 1.0, 1.0 };
	
	if(this->flagATravar)
	{
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_amb_shininess);
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	else
	{
		glColor3f(0.5f, 0.0f, 0.0f);
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff);
	glPushMatrix();
		glTranslatef(-comprimento * 0.5f, (altura / 4.0f) * 1.1, (largura / 2.0f) * 0.85f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		geraPoligono::cilindroFechado(1.0f, largura / 24.0f, largura / 30.0f, 12.0f, 1.0f);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-comprimento * 0.5f, (altura / 4.0f) * 1.1, -(largura / 2.0f) * 0.85f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		geraPoligono::cilindroFechado(1.0f, largura / 24.0f, largura / 30.0f, 12.0f, 1.0f);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_SHININESS, this->shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,mat_amb_diff2);
	glColor3f(cor[0], cor[1], cor[2]);
}
void veiculo::geraDLCarroceria()
{

	// Create o id para a lista
	this->dl_carroceria = glGenLists(1);
	
	// inicializa a lista
	glNewList(this->dl_carroceria,GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		desenhaCarroceria();
		desenhaEixos();
	// termina a lista
	glEndList();
}

void veiculo::loadTextures()
{
	char buffer[256];
	string temp;

	for(int i=0; i<12;i++)
	{
		temp = pathTexturas + texNames[i];
		strncpy(buffer, temp.c_str(), 255);
		texturas[i].LoadTextures(buffer);
	}
}
