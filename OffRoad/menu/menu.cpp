#include"menu.h"

#pragma warning(disable: 4996)

menu::menu(const GLfloat r, GLfloat opcoes, GLfloat altPainel)
		:mundo(-9.80665f)
{
	this->raio = r;
	this->sectores = opcoes;
	this->alturaPainel = altPainel;
	this->anguloSectores = 360.0f / this->sectores;
	this->larguraPainel = -(GLfloat)(sin(this->anguloSectores * 0.5f)) * this->raio * 2.0f;
	this->ang = 0;
	this->pathTexturas = "texturas/menu/";

	this->nrCondicoesAtmosfericas = 4;
	this->condicoesAtmosfericas[0] = "Dia";
	this->condicoesAtmosfericas[1] = "Dia com nevoeiro";
	this->condicoesAtmosfericas[2] = "Noite";
	this->condicoesAtmosfericas[3] = "Noite com nevoeiro";
	this->nrVoltas[0] = "1";
	this->nrVoltas[1] = "3";
	this->nrVoltas[2] = "5";
	this->nrVoltas[3] = "7";

	this->resolucoes[0] = "800x600";
	this->resolucoes[1] = "1024x768";
	this->resolucaoSeleccionada = 1;
	this->resolucaoAnterior = "1024x768";
	this->flagMostraTeclas = false;
	
	glfLoadFont("fonts/arial1.glf");

	this->mundo.setStepTime(2.0f);
	
	this->primeiraVez = true;

	this->iniciaMenu();

	this->initTextNames();
}

menu::~menu()
{
	for(int i = 0 ; i < NR_TEXTURAS_MENU ; i++)
	{
		glDeleteLists(texturas[i].GetID(),1);
		texturas[i].~textura();
	}
}

void menu::restart()
{
	destroy();
	GLfloat corJante[] = {0.0f, 0.4f, 0.0f};
	this->veiculos[0].veic = new veiculo();
	this->veiculos[0].veicNeve = new veiculo("texturas/veiculos/default/neve/", corJante);
	this->veiculos[0].nome = "Willys";
	GLfloat corJante2[] = {0.5f, 0.0f, 0.0f};
	this->veiculos[1].veic = new veiculo("texturas/veiculos/red/", corJante2);
	this->veiculos[1].veicNeve = new veiculo("texturas/veiculos/red/", corJante2);
	this->veiculos[1].nome = "Wrangler";
	this->carregaPistas();
	this->contaRenderizacoes = 0;
}

void menu::iniciaMenu()
{
	this->veiculoSeleccionado = 0;//o primeiro dos veiculos
	this->pistaSeleccionada = 0;
	this->opcaoConfiguracaoSeleccionada = 0;
	this->nrPistas = 0;//variavel para guardar o numero topal de pistas;
	this->opcaoSeleccionada = 0;
	this->condicaoAtmosfericaSeleccionada = 0;

	GLfloat corJante[] = {0.0f, 0.4f, 0.0f};
	this->veiculos[0].veic = new veiculo();
	this->veiculos[0].veicNeve = new veiculo("texturas/veiculos/default/neve/", corJante);
	this->veiculos[0].nome = "Willys";
	
	GLfloat corJante2[] = {0.5f, 0.0f, 0.0f};
	this->veiculos[1].veic = new veiculo("texturas/veiculos/red/", corJante2);
	this->veiculos[1].veicNeve = new veiculo("texturas/veiculos/red/", corJante2);
	this->veiculos[1].nome = "Wrangler";

	//variaveis de controlo dos menu
	this->estaPistaSeleccionada = false;
	this->estaVeiculoSeleccionado = false;
	this->estaCondicaoAtmosfericaSeleccionada = false;
	this->flagMostraMoldura = false;
	this->flagMostraLinha = false;
	this->frames = 0;
	this->submenuActivo = -1;//caso de se encontrar no menu principal da aplicação
	this->contaRenderizacoes = 0;
	
	this->aRodarPraDireita = false;
	this->aRodarPraEsquerda = false;
	this->angRodado = 0.0f;
	this->iniciaJogo = false;
	
	this->estaNrVoltasSeleccionado = false;
	this->nrVoltasSeleccionado = 0;
	this->carregaPistas();
}

void menu::destroy()
{
	for(int i = 0 ; i < this->nrPistas ; i++)
	{
		this->pistas[i].track->~Pista();
		this->pistas[i].pistaODE->~ODETrack();
	}

	for(int i = 0 ; i < NR_VEICULOS ; i++)
	{
		if(i == this->veiculoSeleccionado)
		{
			if(this->pistas[this->pistaSeleccionada].pistaODE->getGroundSurface() == ODETrackSegmentDefinition::Ice || this->pistas[this->pistaSeleccionada].pistaODE->getGroundSurface() == ODETrackSegmentDefinition::Snow)
			{
				this->veiculos[i].veic->~veiculo();
			}
			else
			{
				this->veiculos[i].veicNeve->~veiculo();
			}
		}
		else
		{
			this->veiculos[i].veic->~veiculo();
			this->veiculos[i].veicNeve->~veiculo();
		}
	}
}

ODESimulation& menu::getMundo()
{
	return this->mundo;
}

veiculo * menu::getVeiculo()
{
	if(this->pistas[this->pistaSeleccionada].pistaODE->getGroundSurface() == ODETrackSegmentDefinition::Ice || this->pistas[this->pistaSeleccionada].pistaODE->getGroundSurface() == ODETrackSegmentDefinition::Snow)
		return this->veiculos[this->veiculoSeleccionado].veicNeve;
	else
		return this->veiculos[this->veiculoSeleccionado].veic;
}

const char * menu::getPista()
{
	return this->pistas[this->pistaSeleccionada].ficheiro.c_str();
}

bool menu::getJogo()
{
	return this->iniciaJogo;
}

weather menu::getWeather()
{
	return (weather)this->condicaoAtmosfericaSeleccionada;
}

int menu::getNrVoltas()
{
	return atoi(this->nrVoltas[this->nrVoltasSeleccionado]);
}

void menu::rodaMenu(GLfloat angulo)
{
	this->ang += angulo;
}

void menu::anterior()
{
	switch(this->getMenuActivo())
	{
		case -1:
			if(!this->aRodarPraDireita && !this->aRodarPraEsquerda && this->submenuActivo == -1)
			{
				this->aRodarPraDireita = true;
				this->angRodado = 0.0f;
				if(this->opcaoSeleccionada == 0)
					this->opcaoSeleccionada = this->sectores - 1;
				else
					this->opcaoSeleccionada -= 1;
			}
		break;

		case 0:
			if(!this->estaVeiculoSeleccionado)
			{
				if(this->veiculoSeleccionado == NR_VEICULOS - 1)
					this->veiculoSeleccionado = 0;
				else
					this->veiculoSeleccionado++;
			}
			else
			{
				if(!this->estaPistaSeleccionada)
				{
					if(this->pistaSeleccionada == this->nrPistas -1)
						this->pistaSeleccionada = 0;
					else
						this->pistaSeleccionada++;
				}
				else
				{
					if(!this->estaCondicaoAtmosfericaSeleccionada)
					{
						if(this->condicaoAtmosfericaSeleccionada == 0)
							this->condicaoAtmosfericaSeleccionada = this->nrCondicoesAtmosfericas -1;
						else
							this->condicaoAtmosfericaSeleccionada--;
					}
					else
					{
						if(!this->estaNrVoltasSeleccionado)
						{
							if(this->nrVoltasSeleccionado == 0)
								this->nrVoltasSeleccionado = NR_NR_VOLTAS - 1;
							else
								this->nrVoltasSeleccionado--;
						}
					}
				}
			}
		break;

		case 1:
			if(this->opcaoConfiguracaoSeleccionada == 0)
			{
				if(this->resolucaoSeleccionada > 0)
					{
						this->resolucaoSeleccionada--;
					}
			}
		break;
	}
}

void menu::proximo()
{
	switch(this->getMenuActivo())
	{
		case -1:
			if(!this->aRodarPraDireita && !this->aRodarPraEsquerda && this->submenuActivo == -1)
			{
				this->aRodarPraEsquerda = true;
				this->angRodado = 0.0f;
				if(this->opcaoSeleccionada == this->sectores - 1)
					this->opcaoSeleccionada = 0;
				else
					this->opcaoSeleccionada += 1;
			}
		break;

		case 0:
			if(!this->estaVeiculoSeleccionado)
			{
				if(this->veiculoSeleccionado == 0)
					this->veiculoSeleccionado = NR_VEICULOS - 1;
				else
					this->veiculoSeleccionado--;
			}
			else
			{
				if(!this->estaPistaSeleccionada)
				{
					if(this->pistaSeleccionada == 0)
						this->pistaSeleccionada = this->nrPistas -1;
					else
						this->pistaSeleccionada--;
				}
				else
				{
					if(!this->estaCondicaoAtmosfericaSeleccionada)
					{
						if(this->condicaoAtmosfericaSeleccionada == this->nrCondicoesAtmosfericas -1)
							this->condicaoAtmosfericaSeleccionada = 0;
						else
							this->condicaoAtmosfericaSeleccionada++;
					}
					else
					{
						if(!this->estaNrVoltasSeleccionado)
						{
							if(this->nrVoltasSeleccionado == NR_NR_VOLTAS -1)
								this->nrVoltasSeleccionado = 0;
							else
								this->nrVoltasSeleccionado++;
						}	
					}
				}
			}
		break;
		
		case 1:
			if(this->opcaoConfiguracaoSeleccionada == 0)
			{
				if(this->resolucaoSeleccionada < NR_RESOLUCOES - 1)
				{
					this->resolucaoSeleccionada++;
				}
			}
		break;
	}
}

void menu::cima()
{
	if(this->getMenuActivo() == 1)//encontra-se no menu opcoes
	{
		if(this->opcaoConfiguracaoSeleccionada > 0)
		{
			this->opcaoConfiguracaoSeleccionada--;
		}
	}
}

void menu::baixo()
{
	if(this->getMenuActivo() == 1)//encontra-se no menu opcoes
	{
		if(this->opcaoConfiguracaoSeleccionada < NR_OP_CONFIGURACAO -1)
		{
			this->opcaoConfiguracaoSeleccionada++;
		}
	}
}

void menu::abreMenu()
{
	this->submenuActivo = this->opcaoSeleccionada;
}

void menu::voltaAoPrincipal()
{
	this->submenuActivo = -1;
}

GLint menu::getMenuActivo()
{
	return this->submenuActivo;
}

void menu::pressEnter()
{
	switch(this->getMenuActivo())
	{
		case -1:	
			this->resolucaoAnterior = this->resolucoes[this->resolucaoSeleccionada];
			this->abreMenu();
		break;
		
		case 0:
		
			if(!this->estaVeiculoSeleccionado)
			{
				this->estaVeiculoSeleccionado = true;
			}
			else
			{
				if(!this->estaPistaSeleccionada)
				{
					this->estaPistaSeleccionada = true;
				}
				else
				{
					if(!this->estaCondicaoAtmosfericaSeleccionada)//ainda falta ver se seleccionou o tempo 
					{
						this->estaCondicaoAtmosfericaSeleccionada = true;
						Weather::activeWeather = (weather)this->condicaoAtmosfericaSeleccionada;
					}
					else
						if(!this->estaNrVoltasSeleccionado)
						{
							this->estaNrVoltasSeleccionado = true;
							this->iniciaJogo = true;
						}
				}
			}
		break;

		case 1:
				if(this->opcaoConfiguracaoSeleccionada == 1 && !this->flagMostraTeclas)
				{
					this->flagMostraTeclas = true;
				}
		break;
	}
}

void menu::pressEscape()
{
	switch(this->getMenuActivo())
	{
		case 0:
			if(!this->estaVeiculoSeleccionado)
			{
				this->submenuActivo = -1;
				this->veiculoSeleccionado = 0;
				this->condicaoAtmosfericaSeleccionada = 0;
				this->pistaSeleccionada = 0;
				this->nrVoltasSeleccionado = 0;
			}
			else
				if(!this->estaPistaSeleccionada)
				{
					this->estaVeiculoSeleccionado = false;
				}
				else
				{
					if(!this->estaCondicaoAtmosfericaSeleccionada && !this->estaNrVoltasSeleccionado)
					{
						this->estaPistaSeleccionada = false;
					}
					else
					{
						if(!this->estaNrVoltasSeleccionado)
						{
							this->estaCondicaoAtmosfericaSeleccionada = false;
						}
						else
						{
								this->estaNrVoltasSeleccionado = false;
						}
					}
				}
		break;

		case 1:
			if(this->opcaoConfiguracaoSeleccionada == 1)
			{
				if(this->flagMostraTeclas)
					{
						this->flagMostraTeclas = false;
					}
				else
				{
					if(!this->flagMostraTeclas)
					{
						this->opcaoConfiguracaoSeleccionada = 0;
						this->submenuActivo = -1;
					}
				}
			}
			else
			{
				this->opcaoConfiguracaoSeleccionada = 0;
				this->submenuActivo = -1;
			}
		break;
		
		default:
			this->submenuActivo = -1;
		break;
	}
}

void menu::desenha()
{
	if(this->contaRenderizacoes < 1)
	{
		this->loadTextures();
	}
	this->contaRenderizacoes++;
	
	switch(this->submenuActivo)
	{
		case -1:
			desenhaFundo(this->texturas[5]);
			desenhaMenuPrincipal();
			break;
		case 0:
			//desenha menu novo jogo
			desenhaFundo(this->texturas[8]);
			desenhaNovoJogo();
			//desenhaBotao();
			break;
		case 1:
			//desenha opcoes
			if(!this->flagMostraTeclas)
			{
				desenhaFundo(this->texturas[9]);
				desenhaMenuOpcoes();
			}
			else
			{
				desenhaFundo(this->texturas[12]);
			}
			//desenhaBotao();
			break;
		case 2:
			//mostra recorde
			desenhaFundo(this->texturas[7]);
			desenhaMelhorTempo();
			//desenhaBotao();
			break;
		case 3:
			//mostr acerca
			desenhaFundo(this->texturas[6]);
			//desenhaBotao();
			break;
		case 4:
			exit(-1);
			break;
			//sair
	}

	if (this->contaRenderizacoes == 1 && this->primeiraVez)
	{
		this->primeiraVez = false;
		destroy();
		GLfloat corJante[] = {0.0f, 0.4f, 0.0f};
		this->veiculos[0].veic = new veiculo();
		this->veiculos[0].veicNeve = new veiculo("texturas/veiculos/default/neve/", corJante);
		this->veiculos[0].nome = "Willys";
		GLfloat corJante2[] = {0.5f, 0.0f, 0.0f};
		this->veiculos[1].veic = new veiculo("texturas/veiculos/red/", corJante2);
		this->veiculos[1].veicNeve = new veiculo("texturas/veiculos/red/", corJante2);
		this->veiculos[1].nome = "Wrangler";
		this->carregaPistas();
	}
	animaMenu();

}

void menu::animaMenu()
{
	if(this->aRodarPraDireita)
	{
		if(this->angRodado < this->anguloSectores)
		{
			this->angRodado += this->anguloSectores * 0.1f;
			this->rodaMenu(this->anguloSectores * 0.1f);
			glutPostRedisplay();
		}
		else
			this->aRodarPraDireita = false;
	}

	if(this->aRodarPraEsquerda)
	{
		if(this->angRodado < this->anguloSectores)
		{
			this->angRodado += this->anguloSectores * 0.1f;
			this->rodaMenu(-this->anguloSectores * 0.1f);
			glutPostRedisplay();
		}
		else
			this->aRodarPraEsquerda = false;
	}
}

void menu::desenhaNovoJogo()
{
	//Desenho da parte dos veiculos
	glPushMatrix();
		glTranslatef(-4.35f, -2.5f, -2.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
			glRotatef(90.0f,1.0f, 0.0f, 1.0f);
			glRotatef(-45.0f,0.0f, 1.0f, 0.0f);
			veiculos[this->veiculoSeleccionado].veic->desenha();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-5.15f, 0.7f, 0.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glfStringDirection(GLF_LEFT);
		glScalef(0.2, 0.4, 0.4);
		glfDrawSolidString(veiculos[this->veiculoSeleccionado].nome);
	glPopMatrix();
	//desenho da parte da seleccao da pista
	glPushMatrix();
		glTranslatef(3.0f, 0.7f, 0.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glfStringDirection(GLF_LEFT);
		glScalef(0.2, 0.4, 0.4);
		glfDrawSolidString(this->pistas[this->pistaSeleccionada].nome);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0f, 0.2f, 0.0f);
		glTranslatef(3.3f,-0.9f, 0.0f);
		glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
		glScalef(0.02f, 0.02f, 0.02f);
		this->pistas[this->pistaSeleccionada].track->desenha();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-5.6f, -6.2f, 0.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glfStringDirection(GLF_LEFT);
		glScalef(0.2, 0.4, 0.4);
		glfDrawSolidString(this->condicoesAtmosfericas[this->condicaoAtmosfericaSeleccionada]);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(4.3f, -6.2f, 0.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glfStringDirection(GLF_LEFT);
		glScalef(0.4, 0.4, 0.4);
		glfDrawSolidString(this->nrVoltas[this->nrVoltasSeleccionado]);
	glPopMatrix();
	
	if(!this->estaVeiculoSeleccionado)
	{	
		this->frames++;
		if(this->frames == 20)
		{
			this->frames = 0;

			if(this->flagMostraMoldura)
				this->flagMostraMoldura = false;
			else
				this->flagMostraMoldura = true;

		}
		if(this->flagMostraMoldura)
		{
			glPushMatrix();
				glTranslatef(-6.15f, 0.0f, 0.0f);
				desenhaMoldura();
			glPopMatrix();
		}
	}
	else
	{
		if(!this->estaPistaSeleccionada)
		{	
			this->frames++;
			if(this->frames == 20)
			{
				this->frames = 0;

				if(this->flagMostraMoldura)
					this->flagMostraMoldura = false;
				else
					this->flagMostraMoldura = true;

			}
			if(this->flagMostraMoldura)
			{
				glPushMatrix();
					glTranslatef(2.15f, 0.0f, 0.0f);
					desenhaMoldura();
				glPopMatrix();
			}
		}
		else
		{
			if(!this->estaCondicaoAtmosfericaSeleccionada)
			{
				this->frames++;
				if(this->frames == 20)
				{
					this->frames = 0;

					if(this->flagMostraLinha)
						this->flagMostraLinha = false;
					else
						this->flagMostraLinha = true;

				}
				if(this->flagMostraLinha)
				{
					glPushMatrix();
						glTranslatef(-6.25, -7.2f, 0.0f);
						desenhaLinha();
					glPopMatrix();
				}
			}
			else
			{
				if(!this->estaNrVoltasSeleccionado)
				{
					this->frames++;
					if(this->frames == 20)
					{
						this->frames = 0;

						if(this->flagMostraLinha)
							this->flagMostraLinha = false;
						else
							this->flagMostraLinha = true;

					}
					if(this->flagMostraLinha)
					{
						glPushMatrix();
							glTranslatef(2.05f, -7.2f, 0.0f);
							desenhaLinha();
						glPopMatrix();
					}
				}
			}
		}
	}
	glutPostRedisplay();
}

void menu::desenhaMenuPrincipal()
{
	desenhaOpcoesMenuPrincipal(this->sectores);
}

void menu::desenhaOpcoesMenuPrincipal(int nrOpcoes)
{
	glPushMatrix();
		glRotatef(this->ang, 0.0f, 1.0f, 0.0f);
		glPushMatrix();
			glPushMatrix();
			glTranslatef(0.0f, -4.0f + this->alturaPainel , 0.0f);
				glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
				this->veiculos[0].veic->desenha();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0f, -4.0f, 0.0f);
				glPushMatrix();
				for(int i = 0 ; i < nrOpcoes ; i++)
				{
					glPushMatrix();
						glRotatef((GLfloat)i * this->anguloSectores, 0.0f, 1.0f, 0.0f);
						this->desenhaOpcaoMenuPrincipal(this->texturas[i]);
					glPopMatrix();
				}
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void menu::desenhaOpcaoMenuPrincipal(textura tx)
{
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, this->raio * 1.365f);
		glColor3f(0.2f, 0.2f, 0.2f);
		glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, this->alturaPainel, -this->raio * 1.365f);//ponto do centro
			glVertex3f(-this->larguraPainel * 0.5f, this->alturaPainel, 0.0f);
			glVertex3f(this->larguraPainel * 0.5f, this->alturaPainel, 0.0f);
		glEnd();
		glPushMatrix();
			glTranslatef(-this->larguraPainel * 0.5f, 0.0f, 0.0f);
			glEnable(GL_TEXTURE_2D);
			tx.SetActive();
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(this->larguraPainel, 0.0f, 0.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(this->larguraPainel, this->alturaPainel, 0.0f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(0.0f, this->alturaPainel, 0.0f);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glPopMatrix();
}

void menu::desenhaFundo(textura tx)
{
	glColor3f(0.0f, 0.5f, 0.0f);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	tx.SetActive();
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-10.0f, -10.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(10.0f, -10.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(10.0f, 10.0f, -4.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-10.0f, 10.0f, -4.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void menu::desenhaMoldura()
{
	glPushMatrix();
	glTranslatef(0.0, -3.0f, 0.0f);
		glPushMatrix();
			glColor3f(0.9f, 0.9f, 0.9f);
			glRectf(0.0f, 0.0f, 0.1f, 5.3f);
			glRectf(0.0f, 0.0f, 4.2f, 0.15f);
			glRectf(4.2f, 0.0f, 4.1f, 5.3f);
			glRectf(0.0f, 5.15f, 4.2f, 5.3f);
		glPopMatrix();
	glPopMatrix();
}

void menu::desenhaLinha()
{
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f);
		glRectf(0.0f, 0.0f, 4.5f, 0.1f);
	glPopMatrix();
}

void menu::desenhaMelhorTempo()
{
	string tempos[10];
	int i = 0;
	ifstream myfile ("recordes.txt");
	char * buffer[10];

	if (myfile.is_open())
	{
		while (! myfile.eof() && i < 11)
		{
			getline (myfile,tempos[i]);
			cout << tempos[i] << endl;
			buffer[i] = const_cast <char *>(tempos[i].c_str());
			i++;
		}
		myfile.close();
	
	}
	else 
	{
		buffer[0] = "Recordes por definir.";
	}

	glfStringCentering(GL_FALSE);
	glfStringDirection(GLF_LEFT);
	glPushMatrix();
		glTranslatef(-6.5f, 1.0f, 0.0f);
		for(int j = 1 ; j < i ; j++)
		{
			glPushMatrix();
				glTranslatef(0.0f, -(j-1) * 0.8f, 0.0f);
				glColor3f(0.9f, 0.9f, 0.9f);
				glScalef(0.16, 0.4, 0.4);
				glfDrawSolidString(buffer[j]);
			glPopMatrix();
		}
	glPopMatrix();
}

void menu::desenhaMenuOpcoes()
{
	switch(this->opcaoConfiguracaoSeleccionada)
	{
		case 0:
			desenhaSeta(-0.3f);
		break;

		case 1:
			desenhaSeta(-1.8f);
		break;

	}

	if(this->resolucaoSeleccionada == 0)
	{
		this->desenhaSeleccionador(0.15f, -0.3f);
	}
	else
	{
		this->desenhaSeleccionador(3.58f, -0.3f);
	}
		
}

void menu::desenhaSeta(GLfloat y)
{
	glPushMatrix();
		glTranslatef(-6.3f, y, 0.0f);
		glEnable(GL_TEXTURE_2D);
		this->texturas[11].SetActive();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.7f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.7f, 0.5f, 1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f, 0.5f, 1.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void menu::desenhaSeleccionador(GLfloat x, GLfloat y)
{
	glPushMatrix();
		glTranslatef(x, y, 0.0f);
		glEnable(GL_TEXTURE_2D);
		this->texturas[10].SetActive();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.4f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.4f, 0.47f, 1.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f, 0.47f, 1.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void menu::desenhaBotao()
{
	//ainda vai ter de receber a textura do botao
	// ou voltar ou sair consoante estiver nos submenus ou no menu principal
	glPushMatrix();
		glTranslatef(5.5f, -6.0f, 5.0f);
		glEnable(GL_TEXTURE_2D);
		this->texturas[13].SetActive();
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, -5.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(2.0f, 0.0f, -5.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(2.0f, 1.2f, -5.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.0f, 1.2f, -5.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void menu::initTextNames()
{
	texNames[0] = "opcao1.bmp";
	texNames[1] = "opcao2.bmp";
	texNames[2] = "opcao3.bmp";
	texNames[3] = "opcao4.bmp";
	texNames[4] = "opcao5.bmp";
	texNames[5] = "fundo.bmp";
	texNames[6] = "acerca.bmp";
	texNames[7] = "melhorTempo.bmp";
	texNames[8] = "novoJogo.bmp";
	texNames[9] = "opcoes.bmp";
	texNames[10] = "seleccionador.bmp";
	texNames[11] = "seta.bmp";
	texNames[12] = "verTeclas.bmp";
	texNames[13] = "botaoVoltar.bmp";
}

void menu::loadTextures()
{
	char buffer[256];
	string temp;

	for(int i = 0; i < NR_TEXTURAS_MENU;i++)
	{
		temp = pathTexturas + texNames[i];
		strncpy(buffer, temp.c_str(), 255);
		texturas[i].LoadTextures(buffer);
	}
}


void menu::carregaPistas()
{
	system("dir /b pistas > listaPistas.txt");
	
	string pista;
	ifstream myfile ("listaPistas.txt");
	int i = 0;
	this->nrPistas = 0;
	if (myfile.is_open())
	{
		while (! myfile.eof() )
		{
			getline (myfile,pista);
			if(pista.find(".trk") && pista != "")
			{
				this->pistas[i].ficheiro = "pistas/";
				this->pistas[i].ficheiro += pista;
				this->pistas[i].pistaODE = new ODETrack(this->mundo,this->pistas[i].ficheiro.c_str());
				this->pistas[i].track = new Pista();
				this->pistas[i].track->CarregaPista(*this->pistas[i].pistaODE);
				this->pistas[i].nome = const_cast <char *>(this->pistas[i].pistaODE->getName().c_str());
				this->nrPistas++;
				i++;
			}
		}
		myfile.close();
	}		
}

/// Devolve a resolução seleccionada.
string menu::getResolution() const
{
	return this->resolucoes[this->resolucaoSeleccionada];
}

string menu::getOldResolution() const
{
	return this->resolucaoAnterior;
}