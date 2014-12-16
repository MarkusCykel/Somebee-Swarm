#include "EditMenu.h"

void EditMenu::render(SDL_Renderer* renderer, const SDL_Rect & viewport)
{
	//SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	//SDL_RenderClear( renderer );
	/*if(a.buttonpressed() == true)
		a.setcolor(0x00, 0xFF, 0x00, 0xFF);
	else
		a.setcolor(0xFF, 0x00, 0x00, 0xFF);*/
	a.render(renderer); 
}

void EditMenu::check_input( int x, int y, const SDL_Rect & viewport)
{
	x = x - viewport.x;
	y = y - viewport.y;
	if(x > 50 && x < 50+50 && y > 50 && y < 50+50 && !a.buttonpressed() )
		a.setbuttonpressed(true);
	else 
		a.setbuttonpressed(false);
}