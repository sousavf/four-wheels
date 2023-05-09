#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include "Segmento.h"
#include "Pista.h"
#include "menu/menu.h"
#include "Carro/veiculo.h"
#include "ODERequirements.h"
#include "ODEHeaders.h"
#include "LapCounter.h"
#include "Utilities.h"
#include "Velocimetro.h"
#include "NrVoltas.h"
#include "camera.h"
#include "CameraControl.h"
#include "Race.h"
#include "Records.h"
#include "ScreenMode.h"
#include "weather.h"
#include "Tempos.h"
#include "QuitConfirm.h"

#include <fmod.h>
#include <fmod_errors.h>
#ifdef WIN32
	#include <windows.h>
	#pragma comment(lib,"fmod/lib/fmod.lib")
#else
	#include <wincompat.h>
#endif

#include <vector>
#include <string>

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace ODE;
using namespace std;

typedef struct Teclas_Press
{
	int up;
	int down;
	int left;
	int right;
}Teclas_Press;

GLfloat cores[3] = {0.5f, 0.5f, 0.5f};
Teclas_Press Teclas;
Velocimetro Speed;
NrVoltas Contador;
Race *race = NULL;
ODECarControl *carControl;
int width,height;

menu menuMain(2.0f, 5.0f, 2.0f);
FSOUND_STREAM * somMenu;
bool jogoADecorrer;
bool voltarMenu = false;

bool isPaused = false;
CameraControl cameraControl;
Records records("recordes.txt");
ScreenMode screen;
Tempos tempos;

void initJogo();
void initMenu();
void timer(int);
void changeSize(int, int);
void OnKeyPress(unsigned char, int, int);
void KeyUp(unsigned char, int, int);
void SpecialKey(int, int, int);
void SpecialKeyUp(int, int, int);


vector< ObstacleType > getObstacles()
{
	vector< ObstacleType > obstacles;
	int count;

	count = Utilities::Random(3, 10);

	while ( (int)obstacles.size() < count )
	{
		int type = Utilities::Random(0, 3);

		if ((ObstacleType)type != Barrel
				&& (ObstacleType)type != StrawBales)
		{
			obstacles.push_back((ObstacleType)type);
		}
	}

	return obstacles;
}

void novoJogo()
{
	initJogo();
	FSOUND_Stream_Close(somMenu);
	const char * pista = menuMain.getPista();
	veiculo *veic = menuMain.getVeiculo();
	menuMain.destroy();
	race = new Race(menuMain.getMundo(), pista, new ODECar(menuMain.getMundo())
				, veic, getObstacles(), menuMain.getNrVoltas());
	carControl = new ODECarControl(race->getCarODE(0));
	Speed.init();
	jogoADecorrer = true;

	if (!race->start())
	{
		exit(-1);
	}
	glutTimerFunc(1, timer, 0);
}


void control()
{
	if(Teclas.up && !Teclas.down)
	{
		if (!carControl->isForward())
		{
			carControl->reverse();
		}
		carControl->setBrake(0.0f);
		carControl->throttle();
	}

	if(Teclas.down)
	{
		if (carControl->isForward()
				&& race->getCarODE(0).getLinearVelocity().length() > 0.1f)
		{
			carControl->setThrottle(0.0f);
			carControl->brake();
		}
		else
		{
			if (carControl->isForward())
			{
				carControl->reverse();
			}
			carControl->throttle();
		}
		race->getCarGL(0).pressionaTravao();		
	}

	if(Teclas.right)
	{
		carControl->steerRight();
		race->getCarGL(0).viraADireita();
	}

	if(Teclas.left)
	{
		carControl->steerLeft();
		race->getCarGL(0).viraAEsquerda();
	}

	if(!Teclas.left && !Teclas.right)
	{
		race->getCarGL(0).vaiEmFrente();
	}

	if(!Teclas.down)
	{
		race->getCarGL(0).soltaTravao();
	}
}


void timer(int n)
{
	if (jogoADecorrer)
	{
		if (!isPaused)
		{
			control();
			carControl->update();
			menuMain.getMundo().step();

			if (race->hasEnded())
			{
				records.add(*race);
				records.save();
				voltarMenu = true;
			}
		}
		
		if(voltarMenu)
		{
			jogoADecorrer = false;
			carControl->~ODECarControl();
			race->~Race();
			initMenu();
			menuMain.iniciaMenu();
			camera::cameraMenu();
			voltarMenu = false;
		}
		glutPostRedisplay();
		glutTimerFunc(1, timer, 0);
	}
}


void renderRace()
{
	if (isPaused)
	{
		QuitConfirm::desenha(width, height);
	}
	//if(race->getCarODE(0).getLinearVelocity().length() > 5)
	//{
	//	race->getCarGL(0).criaSocalco();
	//}
	cameraControl.lookAt(race->getCarODE(0).getPosition(),race->getCarODE(0).getQuaternion().getEulerAngles());
	race->draw();
	Speed.desenha((int)race->getCarODE(0).getLinearVelocity().length(), width, height);
	Contador.desenha(race->getCounter(0).getLaps(),race->getLaps(),width,height);
	tempos.desenha(race->getCounter(0), width, height);
}

void renderScene()
{	
	if(!jogoADecorrer && menuMain.getJogo())
	{
		novoJogo();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(jogoADecorrer)
	{
		renderRace();
	}
	else
	{
		camera::cameraMenu();
		menuMain.desenha();
	}
	
	glFlush();
	glutSwapBuffers();
}

void pause()
{
	if (!isPaused)
	{
		isPaused = true;

		for (int i = 0; i < (int)race->getCounters().size(); i++)
		{
			race->getCounters()[i].stop();
		}
	}
	else
	{
		isPaused = false;

		for (int i = 0; i < (int)race->getCounters().size(); i++)
		{
			race->getCounters()[i].start();
		}
	}
}

//inicializa o nevoeiro
void initFog()
{
	GLfloat fog_color[4]={0.8f,0.8f,0.8f,0.1f};

	// Nevoeiro
	glEnable(GL_FOG);

	glFogi(GL_FOG_MODE,GL_LINEAR); // Linear | Ex
	glFogfv(GL_FOG_COLOR,fog_color);
	glFogf(GL_FOG_START,1.0f);
	glFogf(GL_FOG_END,60.0f);
}

void initWeather()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);//luz ambiente
	glEnable(GL_LIGHT1);
	GLfloat LuzAmbiente [4];
	GLfloat LuzDifusa [] = {1.0,1.0,1.0,1.0};
	GLfloat LuzEspecular [] = {1.0,1.0,1.0,1.0};
	GLfloat LuzPosicao [] = {1.0,1.0,1.0,1.0};
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	
	switch(Weather::activeWeather)
	{
		case Dia :
		case Dia_Nevoeiro :
			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
			for(int i = 0 ; i < 4 ; i++)
			{
				LuzAmbiente[i] = 1.0;
			}
			if(Weather::activeWeather == Dia_Nevoeiro)
				initFog();
		break;

		case Noite :
		case Noite_Nevoeiro :
			//luz ambiente
			glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.005);
			glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.001);
			glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01);
			
			for(int i = 0 ; i < 3 ; i++)
			{
				LuzAmbiente[i] = 0.1;
			}
			
			LuzAmbiente[3] = 1.0;
			
			if(Weather::activeWeather == Noite_Nevoeiro)
				initFog();
		break;
	}
	glLightfv(GL_LIGHT0,GL_AMBIENT,LuzAmbiente);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,LuzDifusa);
	glLightfv(GL_LIGHT0,GL_SPECULAR,LuzEspecular);
	glLightfv(GL_LIGHT0,GL_POSITION,LuzPosicao);
	
	
}

void initJogo()
{
	initWeather();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void initMenu()
{
	if(FSOUND_Init(44000,64,0))
	{
		somMenu = FSOUND_Stream_Open( "sons/intro.mp3" , FSOUND_2D , 0 , 0 );
		FSOUND_Stream_Play(0, somMenu);
	}
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	jogoADecorrer = false;
	camera::cameraMenu();
}

void init()
{
	initMenu();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	Teclas.up = false;
	Teclas.down = false;
	Teclas.left = false;
	Teclas.right = false;
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);
	glutTimerFunc(1, timer, 0);
	glutMainLoop();
}

void OnKeyPress(unsigned char key, int x , int y)
{
	if(jogoADecorrer)
	{
		switch (key)
		{
			case 27:
				pause();
				break;

			case 13:
				if (isPaused)
				{
					voltarMenu = true;
					isPaused = false;
				}
				break;

			case 'c':
				cameraControl.next();
				break;
		}

		if (!isPaused)
		{
			switch (key)
			{
			case 'a':
				Teclas.up = true;
				break;

			case 'z':
				Teclas.down = true;
				break;

			case ' ':
				carControl->handbrake();
				break;
			}
		}
	}
	else
	{
		static string resolution;

		switch (key)
		{
			case 27:
				menuMain.pressEscape();

				if (menuMain.getMenuActivo() == -1 && menuMain.getResolution() != menuMain.getOldResolution())
				{
					ScreenMode::Mode mode =
							(menuMain.getResolution() == "1024x768"
							? ScreenMode::FS_1024x768_32b 
							: ScreenMode::FS_800x600_32b);

					glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

					if (!screen.setMode(mode))
					{
						exit(-1);
					}
					menuMain.restart();
					init();
				}
				break;

			case 13:
				menuMain.pressEnter();
				break;
		}
		glutPostRedisplay();
	}
}

void KeyUp(unsigned char key, int x, int y)
{
/*  switch (key) {

  }*/
}

void SpecialKey(int key, int x, int y)
{
	if(jogoADecorrer)
	{
		if (!isPaused)
		{
			switch (key)
			{
			case GLUT_KEY_UP:
				Teclas.up = true;
				break;

			case GLUT_KEY_DOWN:
				Teclas.down = true;
				break;

			case GLUT_KEY_LEFT:
				Teclas.left = true;
				break;

			case GLUT_KEY_RIGHT:
				Teclas.right = true;
				break;
			}
		}
	}
	else
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			menuMain.cima();
			break;

		case GLUT_KEY_DOWN:
			menuMain.baixo();
			break;

		case GLUT_KEY_LEFT:
			menuMain.anterior();
			break;

		case GLUT_KEY_RIGHT:
			menuMain.proximo();
			break;
		}
		glutPostRedisplay();
	}
}

void SpecialKeyUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		Teclas.up = false;
		break;

	case GLUT_KEY_DOWN:
		Teclas.down = false;
		break;

	case GLUT_KEY_LEFT:
		Teclas.left = false;
		break;

	case GLUT_KEY_RIGHT:
		Teclas.right = false;
		break;
	}
}

void changeSize(int w, int h)
{
	float ratio;

	if(h == 0)
	{
		h = 1;
	}
	ratio = w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	width = w;
	height = h;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	
	if (!screen.setMode(ScreenMode::FS_1024x768_32b))
	{
		return false;
	}
	init();

	return 0;
}