#include "LapCounter.h"

/// Cria um novo contador de voltas.
LapCounter::LapCounter()
{
	this->laps = 0;
}



/// Destrói o contador de voltas.
LapCounter::~LapCounter()
{
}



/// Inicia o contador.
void LapCounter::start()
{
	this->timer.start();
}



/// Pára o contador.
void LapCounter::stop()
{
	this->timer.stop();
}



/// Incrementa o número de voltas e actualiza os tempos.
void LapCounter::incLaps()
{
	this->laps++;
	this->times.push_back(this->timer.getTime());
	this->timer.restart();
}



/// Devolve o número de voltas.
int LapCounter::getLaps() const
{
	return this->laps;
}



/// Devolve o tempo correspondente à volta i (começando em 0).
int LapCounter::getTime(int i) const
{
	return this->times[i];
}



/// Devolve o tempo correspondente à última volta (concluída).
int LapCounter::getLastTime() const
{
	return this->times[(int)this->times.size() - 1];
}



/// Devolve o tempo da volta actual.
int LapCounter::getCurrentTime() const
{
	return this->timer.getTime();
}



/// Devolve o somatório de todos os tempos, incluindo o tempo actual.
int LapCounter::getTotalTime() const
{
	int total = 0;

	for (int i = 0; i < (int)this->times.size(); i++)
	{
		total += this->times[i];
	}
	total += getCurrentTime();

	return total;
}