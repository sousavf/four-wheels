#include "ScreenMode.h"
#include <GL/glut.h>

/// Construtor
ScreenMode::ScreenMode()
{
	resolutions.push_back("1024x768:32");
	resolutions.push_back("1024x768:16");
	resolutions.push_back("800x600:32");
	resolutions.push_back("800x600:16");
}



/// Destructor
ScreenMode::~ScreenMode()
{
}



/// Coloca o ecr� no modo respectivo. Se n�o conseguir tenta o modo abaixo.
/// Devolve false se n�o conseguir colocar em nenhum modo ou true se conseguir
/// num modo, mesmo que n�o seja o passado inicialmente.
bool ScreenMode::setMode(Mode mode)
{
	if (mode == Window800x600)
	{
		glutInitWindowPosition(10, 10);
		glutInitWindowSize(800, 600);

		if (glutCreateWindow("4 Rodas") == GL_FALSE)
		{
			return false;
		}

		return true;
	}
	glutGameModeString(getResolution(mode));

	if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
	{
		if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != GL_FALSE)
		{
			glutLeaveGameMode();
		}
		glutEnterGameMode();

		return true;
	}

	return setMode(next(mode));
}



/// Devolve o modo em que se encontra.
ScreenMode::Mode ScreenMode::getMode() const
{
	return this->current;
}



/// Devolve a string de resolu��o do modo respectivo.
const char* ScreenMode::getResolution(Mode mode)
{
	return this->resolutions[(int)mode].c_str();
}



/// Devolve o pr�ximo modo.
ScreenMode::Mode ScreenMode::next(Mode mode)
{
	return (Mode)( ((int)mode)+1 );
}