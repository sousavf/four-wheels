#include "Timer.h"
#include <Windows.h>

/// Cria um novo temporizador.
Timer::Timer()
{
	reset();
	this->startT = Timer::currentTime();
}



/// Destr�i o temporizador.
Timer::~Timer()
{
}



/// Inicia uma nova contagem.
void Timer::start()
{
	if (this->stopped)
	{
		this->offsetT += (Timer::currentTime() - this->stopT);
		this->stopped = false;
	}

	if (this->toReset)
	{
		this->startT = Timer::currentTime();
		this->toReset = false;
	}
}



/// P�ra a contagem actual.
void Timer::stop()
{
	if (!this->stopped)
	{
		this->stopped = true;
		this->stopT = Timer::currentTime();
	}
}



/// Inicializa o temporizador.
void Timer::reset()
{
	this->toReset = true;
	this->offsetT = 0;
	this->stopped = false;
}



/// Indica o tempo que passou em milissegundos. Se o rel�gio estiver parado
/// indica o tempo que passou desde o in�cio at� ao fim (stop) da contagem.
int Timer::getTime() const
{
	if (this->stopped)
	{
		return this->stopT - this->startT - this->offsetT;
	}

	return Timer::currentTime() - this->startT - this->offsetT;
}



/// Indica se o temporizador est� parado.
bool Timer::isStopped() const
{
	return this->stopped;
}



/// Devolve o tempo absoluto actual.
int Timer::currentTime()
{
	return (int) GetTickCount();
}



/// P�ra o temporizador. Reinicia e come�a de novo a contagem.
void Timer::restart()
{
	stop();
	reset();
	start();
}