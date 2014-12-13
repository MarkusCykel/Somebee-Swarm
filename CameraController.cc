#include "CameraController.h"

void CameraController::setPosition(double x, double y)
{
	posX_ = x;
	posY_ = y;
}

double CameraController::getTargetX()
{
	return targetPosX_;
}

double CameraController::getTargetY()
{
	return targetPosY_;
}

double CameraController::getX()
{
	return posX_;
}

double CameraController::getY()
{
	return posY_;
}
/* Read input and change parameters depending on it */
void CameraController::readInput()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
	
	if( currentKeyStates[ SDL_SCANCODE_W ] ^ currentKeyStates[ SDL_SCANCODE_S ] )
	{
		if(currentKeyStates[ SDL_SCANCODE_W ]) // If it was S, increase speed on x-axis
			if(speedY_ > -maxSpeed_)
				speedY_ -= acceleration_;
			else
				speedY_ = -maxSpeed_;
		else if(currentKeyStates[ SDL_SCANCODE_S ])
			if(speedY_ < maxSpeed_)
				speedY_ += acceleration_;
			else
				speedY_ = maxSpeed_;
	}
	else if( speedY_ < 0 ) // If W nor S is held down, deaccelerate
		speedY_ += acceleration_;
	else if( speedY_ > 0 )
		speedY_ -= acceleration_;
	
	if( currentKeyStates[ SDL_SCANCODE_A ] ^ currentKeyStates[ SDL_SCANCODE_D ] )
	{
		if( currentKeyStates[ SDL_SCANCODE_A ] ) // If it was S, increase speed on x-axis
			if(speedX_ > -maxSpeed_)
				speedX_ -= acceleration_;
			else
				speedX_ = -maxSpeed_;
		else if( currentKeyStates[ SDL_SCANCODE_D ] )
			if(speedX_ < maxSpeed_)
				speedX_ += acceleration_;
			else
				speedX_ = maxSpeed_;
	}
	else if( speedX_ < 0 )
		speedX_ += acceleration_;
	else if( speedX_ > 0 )
		speedX_ -= acceleration_;
	
	
	std::pair<double,double> move_vector{ std::make_pair(speedX_, speedY_) };
	
	double vector_length = sqrt(pow(move_vector.first,2) + pow(move_vector.second, 2));
	
	if(vector_length != 0)
	{
		move_vector_.first = move_vector.first/vector_length;
		move_vector_.second = move_vector.second/vector_length;
	}
}


/* Update position depending on speed */
void CameraController::update(Map& map)
{
	if( targetPosX_ > map.getWidth())
	{
		targetPosX_ = map.getWidth();
	}
	else if( targetPosX_ < 0 )
	{
		targetPosX_ = 0;
	}
	
	if(  targetPosY_ > map.getHeight() )
	{
		targetPosY_ = map.getHeight();
	}
	else if( targetPosY_ < 0 )
	{
		targetPosY_ = 0;
	}
	
	setPosition(targetPosX_, targetPosY_);
	
	if(abs(speedX_) > abs(speedY_))
	{
		targetPosX_ = posX_ + move_vector_.first * abs(speedX_);
		targetPosY_ = posY_ + move_vector_.second * abs(speedX_);
	}
	else
	{
		targetPosX_ = posX_ + move_vector_.first * abs(speedY_);
		targetPosY_ = posY_ + move_vector_.second * abs(speedY_);
	}
}