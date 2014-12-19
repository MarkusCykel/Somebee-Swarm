#ifndef MAPEDITTIMER_H
#define MAPEDITTIMER_H

#include <SDL.h>

class MapEditTimer
{
	public:
		MapEditTimer() : mStartTicks{0}, mPausedTicks{0}, mPaused{false}, mStarted{false} {};
		
		void start();
		void stop();
		void pause();
		void unpause();
		
		Uint32 getTicks();
		
		bool isStarted();
		bool isPaused();
		
	private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
		
		bool mPaused;
		bool mStarted;
};

#endif