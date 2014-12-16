#include "Button.h"

//Just a very long constructor
Button::Button(const SDL_Rect & butt, const Uint8 & R, const Uint8 & G , const Uint8 & B , const Uint8 & A , const bool & press,const std::string& str):
R_{R},G_{G},B_{B},A_{A},buttonpressed_{press},name{str}
{
	button_.x = butt.x;
	button_.y = butt.y;
	button_.w = butt.w;
	button_.h = butt.h;
};

Button::Button(const int & x, const int & y, const int & w, const int & h, const Uint8 & R, const Uint8 & G , const Uint8 & B , const Uint8 & A , const bool & press,const std::string& str):
button_{x,y,w,h}, R_{R},G_{G},B_{B},A_{A},buttonpressed_{press},name{str}{};

Button::Button(): button_{50,50,50,30}, R_{0xFF},G_{0x00},B_{0x00},A_{0xFF},buttonpressed_{false},name{"Wall"}{};


void Button::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor( renderer, R_, G_, B_, A_ );
	SDL_RenderFillRect( renderer, &button_ );
}

void Button::setcolor(const Uint8 & R, const Uint8 & G, const Uint8 & B, const Uint8 & A )
{
	 R_ = R;
	 G_ = G;
	 B_ = B;
	 A_ = A;
}

void Button::setbuttonpressed(const bool & a)
{
	buttonpressed_ = a;
}

void Button::setxywh(int x, int y, int w, int h)
{
	button_.x = x;
	button_.y = y;
	button_.w = w;
	button_.h = h;
}