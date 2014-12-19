#include "Timer.h"

void Timer::start()
{
	//Start the timer
	mStarted = true;
	
	//Unpause the timer
	mPaused = false;
	
	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer
	mStarted = false;
	
	//Unpause the timer
	mPaused = false;
	
	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	if( mStarted && !mPaused )
	{
		mPaused = true;
		
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

Uint32 Timer::getTicks()
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

bool Timer::isStarted()
{
	return mStarted;
}

bool Timer::isPaused()
{
	return mPaused && mStarted;
}

