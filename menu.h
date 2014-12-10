#ifndef MENU_H
#define MENU_H

class SplashScreen
{
public:

private:

};

class Button
{
public:
	Button();
	void setPosistion (int x, int y);
	void handleEvent (SDL_Event* e);
	void render();
private:
	//Top Left position
	SDL_Point mPosition;
	//Currentlu used sprite
	ButtonSprite mCurrentSprite;
};

#endif