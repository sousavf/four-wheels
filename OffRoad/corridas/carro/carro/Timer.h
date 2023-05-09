#ifndef TIMER_H
#define TIMER_H

class Timer
{
	public:
		Timer();
		~Timer();

		void start();
		void stop();
		void reset();
		int getTime() const;
		bool isStopped() const;
		void restart();

	protected:
		int startT;	// o tempo em que começou
		int stopT;	// o tempo em que parou
		bool stopped;
		bool toReset;
		int offsetT;

		static int currentTime();
};

#endif