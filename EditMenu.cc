#include "EditMenu.h"

EditMenu::EditMenu()
{
	Button Wallbutton{50,50,50,30,0xFF,0x00,0x00,0xFF,false,"Wall"};
	Button Spawnerbutton{150,50,50,30,0xFF,0x00,0x00,0xFF,false,"Spawner"};
	buttons_.push_back(Wallbutton);
	buttons_.push_back(Spawnerbutton);
	currentpressed = 0;
}

void EditMenu::render(SDL_Renderer* renderer, const SDL_Rect & viewport)
{
	for(auto & butt : buttons_)
	{
		if(butt.buttonpressed() == true)
		{
			butt.setcolor(0x00, 0xFF, 0x00, 0xFF);
		}
		else
			butt.setcolor(0xFF, 0x00, 0x00, 0xFF);
		butt.render(renderer); 
	}
}

void EditMenu::check_input( int x, int y, const SDL_Rect & viewport)
{
	int counter{0};
	x = x - viewport.x;
	y = y - viewport.y;
	for(auto & butt : buttons_)
	{
		if(x > butt.getx() && x < butt.getx()+butt.getw() && y > butt.gety() && y < butt.gety()+butt.geth() && !butt.buttonpressed() )
		{
			butt.setbuttonpressed(true);
			currentpressed = counter;
		}
		else 
			butt.setbuttonpressed(false);
		counter++;
	}
}