#include "MapEditMenu.h"

MapEditMenu::MapEditMenu()
{
	MapEditButton Savebutton{75,260,70,30,0xFF,0x00,0x00,0xFF,false,"Save"};
	MapEditButton Loadbutton{195,260,70,30,0xFF,0x00,0x00,0xFF,false,"Load"};
	MapEditButton Wallbutton{85,310,50,30,0xFF,0x00,0x00,0xFF,false,"Wall"};
	MapEditButton Spawnerbutton{205,310,50,30,0xFF,0x00,0x00,0xFF,false,"Spawner"};
	MapEditButton PlayerSpawnerbutton{160,350,20,10,0xFF,0x00,0x00,0xFF,false,"PlayerSpawner"};
	MapEditButton Quitbutton{85,400,170,30,0xFF,0x00,0x00,0xFF,false,"Quit"};
	buttons_.push_back(Wallbutton);
	buttons_.push_back(Spawnerbutton);
	buttons_.push_back(PlayerSpawnerbutton);
	buttons_.push_back(Savebutton);
	buttons_.push_back(Loadbutton);
	buttons_.push_back(Quitbutton);
	currentpressed = 0;
}

void MapEditMenu::render(SDL_Renderer* renderer, const SDL_Rect & viewport)
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

void MapEditMenu::check_input( int x, int y, const SDL_Rect & viewport)
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