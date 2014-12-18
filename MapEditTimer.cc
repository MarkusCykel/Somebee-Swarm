#include "MapEditTimer.h"

void MapEditTimer::start()
{
	//Start the timer
	mStarted = true;
	
	//Unpause the timer
	mPaused = false;
	
	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void MapEditTimer::stop()
{
	//Stop the timer
	mStarted = false;
	
	//Unpause the timer
	mPaused = false;
	
	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void MapEditTimer::pause()
{
	if( mStarted && !mPaused )
	{
		mPaused = true;
		
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

Uint32 MapEditTimer::getTicks()
{
	Uint32 time = 0;
	
	if( mStarted ) 
	{
		if( mPaused )
		{
			time = mPausedTicks;
		}
		else
		{
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	
	return time;
}

bool MapEditTimer::isStarted()
{
	return mStarted;
}

bool MapEditTimer::isPaused()
{
	return mPaused && mStarted;
}

