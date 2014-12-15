#include "EditMenu.h"

void EditMenu::render(SDL_Renderer* renderer, const SDL_Rect & viewport)
{
	//SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//SDL_RenderClear( renderer );
	SDL_Rect fillRect = { 50, 50, 50, 50};
	if(buttonpressed_ == true)
		SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
	else
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );
}

void EditMenu::check_input( int x, int y, const SDL_Rect & viewport)
{
	x = x - viewport.x;
	y = y - viewport.y;
	if(x > 50 && x < 50+50 && y > 50 && y < 50+50 && !buttonpressed_ )
		buttonpressed_ = true;
	else 
		buttonpressed_ = false;
}