#include "MapEditMenu.h"

MapEditMenu::MapEditMenu()
{
	int x, y, w, h;
	
	x = 85;
	y = 100;
	w = 170;
	h = 30;
	
	MapEditButton Wallbutton{x,y,w,h,0xFF,0x00,0x00,0xFF,false,"Wall"};
	y += 40;
	MapEditButton Spawnerbutton{x,y,w,h,0xFF,0x00,0x00,0xFF,false,"Spawner"};
	y += 40;
	MapEditButton PlayerSpawnerbutton{x,y,w,h,0xFF,0x00,0x00,0xFF,false,"PlayerSpawner"};
	y += 40;
	MapEditButton Loadbutton{x,y,w,h,0xFF,0x00,0x00,0xFF,false,"Load"};
	y += 40;
	MapEditButton Savebutton{x,y,w,h,0xFF,0x00,0x00,0xFF,false,"Save"};
	y += 40;
	MapEditButton Quitbutton{x,y,w,h,0xFF,0x00,0x00,0xFF,false,"Quit"};
	
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