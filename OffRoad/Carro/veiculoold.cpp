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
	
	loadTextures();

	/*
	cout << "altura " << altura << endl;
	cout << "largura " << largura << endl;
	cout << "comprimento " << comprimento << endl;
	cout << "raio do eixo " << raioEixo << endl;
	cout << "distanciaCavaRodaAFrente " << distanciaCavaRodaAFrente << endl;
	cout << "distanciaCavaRodaATras " << distanciaCavaRodaATras << endl;
	cout << "distanciaRodaAoChassis " << distanciaRodaAoChassis << endl;
	cout << "distanciaEixoAoChassis " << distanciaEixoAoChassis << endl;
	cout << "comprimentoCavaDaRoda " << comprimentoCavaDaRoda << endl;
	cout << "larguraCavaDaRoda " << larguraCavaDaRoda << endl;
	cout << "alturaCavaDaRoda " << alturaCavaDaRoda << endl;
	cout << "alturaCapot " << alturaCapot << endl;
	cout << "comprimentoCapot " << comprimentoCapot << endl;
	cout << "larguraTopoCapot " << larguraTopoCapot << endl;
	cout << "comprimentoCabine " << comprimentoCabine << endl;
	cout << "comprimentoCaixa" << comprimentoCaixa << endl;
	*/
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

	loadTextures();
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
	//cout << "pathTex = " << pathTex << endl;
	pathTexturas = pathTex;
	
	//cout << "pathTexturas = " << pathTexturas << endl;

	initVariaveisDependentes();
	initRodas();
	initTextureFiles();

	loadTextures();
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

	loadTextures();
}

veiculo::~veiculo()
{
	/*delete[] &texturas;
	delete[] &texNames;
	delete[] posStops;
	delete[] posFarois;
	delete[] posFocos;*/
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

	angPorta = 0.0f;

	posStops = new GLfloat*[3];
	posStops[0] = new GLfloat[2];
	posStops[1] = new GLfloat[2];

	posFarois = new GLfloat*[3];
	posFarois[0] = new GLfloat[2];
	posFarois[1] = new GLfloat[2];
	
	posFocos = new GLfloat*[3];
	posFocos[0] = new GLfloat[2];
	posFocos[1] = new GLfloat[2];
	posFocos[2] = new GLfloat[2];
	posFocos[3] = new GLfloat[2];
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
	glPushMatrix();
		glTranslatef(posicao.x,posicao.y,posicao.z);
		glRotatef(ang_rot[0],1.0f,0.0f,0.0f);
		glRotatef(ang_rot[1],0.0f,1.0f,0.0f);
		glRotatef(ang_rot[2],0.0f,0.0f,1.0f);
		glPushMatrix();
			//glTranslatef(0.0f,0.0f,altura*1.5f);
			glRotatef(90.0f,1.0f,0.0f,0.0f);
			glRotatef(180.0f,0.0f,0.0f,1.0f);
			desenhaRodas();
			desenhaEixos();
			desenhaCarroceria();
			//glColor3f(1.0f, 0.0f, 0.0f);
			//geraPoligono::cubo(1.87f, 3.88f, 0.61f);
		glPopMatrix();
	glPopMatrix();
}

//adiciona o angulo recebido ao já definido na roda
//altera isto para as rodas rodarem independenters
void veiculo::virarRodaDireita(GLfloat ang_y)
{
	rodas.f_dir.setRotacaoY(rodas.f_dir.getRotacaoY() + ang_y);
}

void veiculo::virarRodaEsquerda(GLfloat ang_y)
{
	rodas.f_esq.setRotacaoY(rodas.f_esq.getRotacaoY() + ang_y);
}

void veiculo::rotacaoRodas(GLfloat ang_z)
{
	rodas.f_esq.setRotacaoZ(rodas.f_esq.getRotacaoZ() + ang_z);
	rodas.t_dir.setRotacaoZ(rodas.t_dir.getRotacaoZ() - ang_z);
	rodas.f_dir.setRotacaoZ(rodas.f_dir.getRotacaoZ() - ang_z);
	rodas.t_esq.setRotacaoZ(rodas.t_esq.getRotacaoZ() + ang_z);
}

GLfloat** veiculo::getPosicaoStops()
{
	posStops[0][0] = (posicao.x - comprimento * 0.5f);
	posStops[0][1] = posicao.y + (altura * 0.25f * 1.1f);
	posStops[0][2] = posicao.z + (largura * 0.5f * 0.85f);
	posStops[1][0] = (posicao.x - comprimento * 0.5f);
	posStops[1][1] = posicao.y + (altura * 0.25f * 1.1f);
	posStops[1][2] = posicao.z - (largura * 0.5f * 0.85f);
	
	 return posStops;
}

GLfloat** veiculo::getPosicaoFarois()
{
	posFarois[0][0] = posicao.x + comprimento * 0.48f;
	posFarois[0][1] = posicao.y + altura * 0.5f - largura * 0.125f;
	posFarois[0][2] = posicao.z - largura * 0.350f;
	posFarois[1][0] = posicao.x - comprimento * 0.48f;
	posFarois[1][1] = posicao.y + altura * 0.5f - largura * 0.125f;
	posFarois[1][2] = posicao.z + largura * 0.35f;
	
	 return posFarois;
}

GLfloat** veiculo::getPosicaoFocos()
{
	GLfloat tempX = - comprimentoCabine * 0.5f + largura / 24.0f;
	GLfloat tempY = altura * 0.5f + largura / 12.0f;

	posFocos[0][0] = posicao.x + tempX;
	posFocos[0][1] = posicao.y + tempY;
	posFocos[0][2] = posicao.z + largura * 0.5f - largura / 32.0f;
	posFocos[1][0] = posicao.x + tempX;
	posFocos[1][1] = posicao.y + tempY;
	posFocos[1][2] = posicao.z + largura * 0.5f - largura / 4.0f - largura / 32.0f;
	posFocos[2][0] = posicao.x + tempX;
	posFocos[2][1] = posicao.y + tempY;
	posFocos[2][2] = posicao.z + largura / 32.0f;
	posFocos[3][0] = posicao.x + tempX;
	posFocos[3][1] = posicao.y + tempY;
	posFocos[3][2] = posicao.z - 0.25f * largura -largura / 32.0f;

	return posFocos;
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
	/*cout << "comprimento :" << comprimento << endl;
	cout << "largura :" << largura << endl;
	cout << "comprimentocava da roda :" << comprimentoCavaDaRoda << endl;
	cout << "largura cava da roda :" << larguraCavaDaRoda << endl;*/
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
	//desenha lado esquerdo até meio
	glPushMatrix();
		glTranslatef(0.0f,0.0f,(largura/2.0));
		desenhaPainelLateralCentral();
	glPopMatrix();
	//desenha lado direito até meio
	glPushMatrix();
		glTranslatef(0.0f,0.0f,(-largura/2.0));
		desenhaPainelLateralCentral();
	glPopMatrix();
	display_list_cava_da_roda = geraDLCavaDaRoda();
	glPushMatrix();
		desenhaCavasDasRodas();
	glPopMatrix();
	//desenha a frente do carro ate metade
	desenhaFrenteAteMeio();
	//desenha a traseira do carro até meio
	desenhaTraseiraAteMeio();
	glDeleteLists(display_list_cava_da_roda, 1);
}
void veiculo::desenhaPainelLateralCentral()
{
	//painel tras
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[6].SetActive();
	}
	glBegin(GL_QUADS);
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
	geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0f) + distanciaCavaRodaATras + comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras, alturaCavaDaRoda);
	geraPoligono::triangulo((-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda, alturaCavaDaRoda, (-comprimento / 2.0f) + distanciaCavaRodaATras + (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda);
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
	glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda ,(comprimento / 2.0f) - distanciaCavaRodaAFrente , altura/2.0);
	geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente, alturaCavaDaRoda / 2.0f, (comprimento / 2.0f) - distanciaCavaRodaAFrente, alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda / 4.0f, alturaCavaDaRoda);
	geraPoligono::triangulo((comprimento / 2.0) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda / 2.0f, (comprimento / 2.0) - distanciaCavaRodaAFrente - (comprimentoCavaDaRoda * (3.0f / 4.0f)), alturaCavaDaRoda, (comprimento / 2.0f) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda, alturaCavaDaRoda);
	//painel frente direita
	glRectf((comprimento / 2.0f) - distanciaCavaRodaAFrente, 0.0f ,(comprimento / 2.0f), altura / 2.0f);
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
}

void veiculo::desenhaCavasDasRodas()
{
	//desenha cava da roda de tras direita
	glPushMatrix();
		glTranslatef((-comprimento / 2.0) + distanciaCavaRodaATras,0.0f,(largura / 2.0) - larguraCavaDaRoda);
		glCallList(display_list_cava_da_roda);
	glPopMatrix();
	//frente direita
	glPushMatrix();
		glTranslatef((comprimento / 2.0) - distanciaCavaRodaAFrente - comprimentoCavaDaRoda,0.0f,(largura / 2.0) - larguraCavaDaRoda);
		glCallList(display_list_cava_da_roda);
	glPopMatrix();
	//tras esquerda
	glPushMatrix();
		glTranslatef((-comprimento / 2.0) + distanciaCavaRodaATras + comprimentoCavaDaRoda,0.0f,-(largura / 2.0) + larguraCavaDaRoda);
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		glCallList(display_list_cava_da_roda);
	glPopMatrix();
	//frente esquerda
	glPushMatrix();
		glTranslatef((comprimento / 2.0) - distanciaCavaRodaAFrente,0.0f,-(largura / 2.0) + larguraCavaDaRoda);
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		glCallList(display_list_cava_da_roda);
	glPopMatrix();
}

void veiculo::desenhaCavaDaRoda()
{	
	if(flagTexturas)
	{
		glEnable(GL_TEXTURE_2D);
		texturas[8].SetActive();
	}
	glPushMatrix();
		glRotatef(-90.0f,0.0f,1.0f,0.0f);
		glRectf(0.0f,0.0f,larguraCavaDaRoda,alturaCavaDaRoda);
	glPopMatrix();
	//parte de cima
	glPushMatrix();
		glTranslatef(0.0f,alturaCavaDaRoda,larguraCavaDaRoda);
		glRotatef(-90.0f,1.0f,0.0f,0.0f);
		glRectf(0.0f,0.0f,comprimentoCavaDaRoda,larguraCavaDaRoda);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(comprimentoCavaDaRoda,0.0f,0.0f);
		glRotatef(-90.0f,0.0f,1.0f,0.0f);
		glRectf(0.0f,0.0f,larguraCavaDaRoda,alturaCavaDaRoda);
	glPopMatrix();
	//parte de dentro
	glPushMatrix();
		glRectf(0.0f,0.0f,comprimentoCavaDaRoda,alturaCavaDaRoda);
	glPopMatrix();
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
}

GLuint veiculo::geraDLCavaDaRoda()
{
	GLuint lista;

	// Create o id para a lista
	lista = glGenLists(1);
	
	// inicializa a lista
	glNewList(lista,GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		desenhaCavaDaRoda();

	// termina a lista
	glEndList();
	
	return(lista);
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
			}//textura da traseira(parte de cima)
			glBegin(GL_QUADS);
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
	GLuint display_janela_cabine = geraDLJanelaCabine();
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
			glRectf(0.0f,0.0f,largura, alturaCapot);
			if(flagTexturas)
			{
				glDisable(GL_TEXTURE_2D);
			}
		glPopMatrix();
		//desenha a janela do lado esquerdo
		glPushMatrix();
			glCallList(display_janela_cabine);
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
			glCallList(display_janela_cabine);
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
	glDeleteLists(display_janela_cabine, 1);
}


void veiculo::desenhaJanelaCabine()
{
	glPushMatrix();
			glTranslatef(-comprimentoCabine / 2.0, 0.0f, (largura / 2.0));
			if(flagTexturas)
			{
				glEnable(GL_TEXTURE_2D);
				texturas[4].SetActive();
			}
			glRectf(0.0f,0.0f,comprimentoCabine,alturaCapot);
			glPushMatrix();
				glTranslatef(0.0f, alturaCapot, 0.0f);
				//friso de tras do vidro
				glRectf(0.0f, 0.0f, (comprimentoCabine)* 0.1, (altura / 2.0f) - alturaCapot);
				glTranslatef((comprimentoCabine * 0.1f), 0.0f, 0.0f);
				//friso da frente do vidro
				glBegin(GL_QUADS);
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
				glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				geraPoligono::triangulo(0.0f, 0.0f, comprimentoCabine * 0.8f, 0.0f, 0.0f, ((altura / 2.0f) * 0.9f) - alturaCapot);
				glDisable(GL_BLEND);
				glColor3f(cor[0], cor[1], cor[2]);
			glPopMatrix();
		glPopMatrix();
}

GLuint veiculo::geraDLJanelaCabine()
{
	GLuint lista;

	// Create o id para a lista
	lista = glGenLists(1);
	
	// inicializa a lista
	glNewList(lista,GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		desenhaJanelaCabine();

	// termina a lista
	glEndList();
	
	return(lista);
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
	glRectf(0.0f, 0.0f, largura, alturaParaBrisas * 0.1f);
	//friso da esquerda
	glRectf(0.0f, alturaParaBrisas * 0.1f, largura * 0.05f, alturaParaBrisas * 0.9f);
	//friso da direita
	glRectf(largura * 0.95f, alturaParaBrisas * 0.1f, largura, alturaParaBrisas * 0.9f);
	//friso superior
	glRectf(0.0f, alturaParaBrisas * 0.9f, largura, alturaParaBrisas);
	if(flagTexturas)
	{
		glDisable(GL_TEXTURE_2D);
	}
	//janela
	glColor4f(0.0f,0.0f,1.0f,0.5f);
	glEnable (GL_BLEND); glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRectf(largura * 0.05f, alturaParaBrisas * 0.1f, largura * 0.95f, alturaParaBrisas * 0.9f);
	glDisable(GL_BLEND);
	glColor3f(cor[0], cor[1], cor[2]);
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
		glTranslatef(-(comprimento / 2.0f), 0.0f, 0.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		suplente.desenha();
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
	GLfloat LuzAmbiente []={0.2,0.2,0.2,1.0};
	GLfloat LuzDifusa []={1.0,1.0,1.0,1.0};
	GLfloat LuzEspecular []={1.0,1.0,1.0,1.0};
	GLfloat LuzPosicao []={1.0,1.0,1.0,1.0};
	GLfloat LuzDireccao []={1.0f, 0.0f, 1.0f, 0.0f};

	GLuint display_foco = geraDLFoco();
	
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
				/*glLightfv(GL_LIGHT0,GL_AMBIENT,LuzAmbiente);
				glLightfv(GL_LIGHT0,GL_DIFFUSE,LuzDifusa);
				glLightfv(GL_LIGHT0,GL_SPECULAR,LuzEspecular);
				glLightfv(GL_LIGHT0,GL_POSITION,LuzPosicao);
				glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,45.0f);
				glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,LuzDireccao);*/
				glCallList(display_foco);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(0.0f, 0.0f, -largura / 4.0f);
				glCallList(display_foco);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, -largura * 0.5f);
				glCallList(display_foco);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, 0.0f, - 0.75 * largura);
				glCallList(display_foco);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glDeleteLists(display_foco, 1);
}

void veiculo::desenhaFoco()
{
	GLfloat larguraFoco = largura / 8.0f;
	GLfloat alturaFoco = larguraFoco * (2.0f /3.0f);
	GLfloat profundidadeFoco = alturaFoco / 2.0f;
	
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
			//glRectf(0.0f, 0.0f, larguraFoco, alturaFoco);
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
}


void veiculo::desenhaStops()
{
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(cor[0], cor[1], cor[2]);
}
GLuint veiculo::geraDLFoco()
{
	GLuint lista;

	// Create o id para a lista
	lista = glGenLists(1);
	
	// inicializa a lista
	glNewList(lista,GL_COMPILE);

	// chamada da funcao que contem 
	// os comandos de renderização
		desenhaFoco();

	// termina a lista
	glEndList();
	
	return(lista);
}
void veiculo::loadTextures()
{
	char buffer[256];
	string temp;

	for(int i=0; i<12;i++)
	{
		temp = pathTexturas + texNames[i];
		//cout << temp << endl;
		strncpy(buffer, temp.c_str(), 255);
		texturas[i].LoadTextures(buffer);
	}
}

void veiculo::initLuzes()
{
	//GLfloat fog_color[4]={0.5f,0.5f,0.5f,0.5f};

	//// Nevoeiro
	////glEnable(GL_FOG);
	//

	//glFogi(GL_FOG_MODE,GL_LINEAR); // Linear | Ex

	//glFogfv(GL_FOG_COLOR,fog_color);
	//glFogf(GL_FOG_START,1.0f);
	//glFogf(GL_FOG_END,40.0f);


	// Foco
	



}