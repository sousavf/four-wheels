#ifndef LAPCOUNTER_H
#define LAPCOUNTER_H

#include "Timer.h"
#include <vector>

using namespace std;

class LapCounter
{
public:
	LapCounter();
	~LapCounter();

	void start();
	void stop();
	void incLaps();

	int getLaps() const;
	int getTime(int i) const;
	int getLastTime() const;
	int getCurrentTime() const;
	int getTotalTime() const;

protected:
	int laps;
	vector< int > times;
	Timer timer;
};

#endif