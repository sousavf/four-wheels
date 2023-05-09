#include "Rails.h"


Rails::Rails()
{
	this->AlturaAoChao = 0.6f;
	this->AlturaRail = 1.0f;
	this->GrossuraPilares = 0.005f;
	this->StartPilares = -0.1f;
}

void Rails::init()
{
	this->RailText.LoadTextures("texturas/rails/rail.bmp");
}


void Rails::desenha(GLfloat TamanhoBloco, int type)
{
	GLfloat Largura;

	Largura = 15;

	glEnable(GL_TEXTURE_2D);

	this->RailText.SetActive();

	glPushMatrix();
		glBegin(GL_QUADS);
	
			switch(type)
			{
				// Arvores ou alguma merda assim
				case -1:

				break;
					
				// --------
				//  --->
				// --------

				case 0:
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f , Largura * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f  , Largura * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f  , Largura  * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f , Largura * 0.5f , this->AlturaAoChao + this->AlturaRail);


					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , Largura * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , Largura * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , Largura  * 0.5f , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , Largura * 0.5f , this->AlturaAoChao);




					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5 , - Largura * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5  , - Largura * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5  , - Largura  * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5 , - Largura * 0.5f , this->AlturaAoChao + this->AlturaRail);	

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , - Largura * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , - Largura * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , - Largura  * 0.5f , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , - Largura * 0.5f , this->AlturaAoChao);
				break;

				// |   ^   |
				// |   |   |
				// |   |   |

				case 1:
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(Largura * 0.5f, -TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(Largura * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(Largura * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(Largura * 0.5f, -TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(Largura * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(Largura * 0.5f  , TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(Largura * 0.5f  , TamanhoBloco  * this->GrossuraPilares , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(Largura * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->AlturaAoChao);

					
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- Largura * 0.5 , - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(- Largura * 0.5  , TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(- Largura * 0.5  , TamanhoBloco  * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- Largura * 0.5 , - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);	

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- Largura * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(- Largura * 0.5f  , TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(- Largura * 0.5f  , TamanhoBloco  * this->GrossuraPilares , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- Largura * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->AlturaAoChao);
				break;

				case 2:
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f, Largura * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f, Largura * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f, Largura * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f, Largura * 0.5f , this->AlturaAoChao + this->AlturaRail);


					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , Largura * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , Largura * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , Largura  * 0.5f , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , Largura * 0.5f , this->AlturaAoChao);



					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- Largura * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(- Largura * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(- Largura * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- Largura * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- Largura * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(- Largura * 0.5f  , TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(- Largura * 0.5f  , TamanhoBloco  * this->GrossuraPilares , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- Largura * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->AlturaAoChao);

				break;

				// |  |  |
				// |  |  |
				// |  |  -----
				// |  ---->
				// ----------
				case 3:
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);

					
					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , - TamanhoBloco * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , - TamanhoBloco * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , - TamanhoBloco  * 0.5f , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , - TamanhoBloco * 0.5f , this->AlturaAoChao);


					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f  , TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f  , TamanhoBloco  * this->GrossuraPilares , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->AlturaAoChao);

				break;


				//       |   ^   |
				//       |   |   |
				// ------    |   |
				//   ---------   |
				// --------------|

				case 4:
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
	
					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , - TamanhoBloco * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , - TamanhoBloco * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , - TamanhoBloco  * 0.5f , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , - TamanhoBloco * 0.5f , this->AlturaAoChao);
						
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f( TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f( TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f( TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f( TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f  , TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f  , TamanhoBloco  * this->GrossuraPilares , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->AlturaAoChao);
				break;

				// ---------------
				//    < - - -     |
				// ------    |    |
				//		|    |    |
				//      |    |    |

				case 5:
					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , TamanhoBloco * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , TamanhoBloco * 0.5f , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * this->GrossuraPilares  , TamanhoBloco  * 0.5f , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(- TamanhoBloco * this->GrossuraPilares , TamanhoBloco * 0.5f , this->AlturaAoChao);

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f( TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f( TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f( TamanhoBloco * 0.5f, TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f( TamanhoBloco * 0.5f, - TamanhoBloco * 0.5f , this->AlturaAoChao + this->AlturaRail);

					// Divisão

					glNormal3f(0.0f,0.0f,1.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(TamanhoBloco * 0.5f  , TamanhoBloco * this->GrossuraPilares , this->StartPilares);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f  , TamanhoBloco * this->GrossuraPilares , this->AlturaAoChao);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(TamanhoBloco * 0.5f , - TamanhoBloco * this->GrossuraPilares , this->AlturaAoChao);
				break;
			}

		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
