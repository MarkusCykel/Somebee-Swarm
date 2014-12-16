#include "EditMenu.h"

void EditMenu::render(SDL_Renderer* renderer, const SDL_Rect & viewport)
{
	if(a.buttonpressed() == true)
		a.setcolor(0x00, 0xFF, 0x00, 0xFF);
	else
		a.setcolor(0xFF, 0x00, 0x00, 0xFF);
	a.render(renderer); 
}

void EditMenu::check_input( int x, int y, const SDL_Rect & viewport)
{
	x = x - viewport.x;
	y = y - viewport.y;
	if(x > a.getx() && x < a.getx()+a.getw() && y > a.gety() && y < a.gety()+a.geth() && !a.buttonpressed() )
		a.setbuttonpressed(true);
	else 
		a.setbuttonpressed(false);
}