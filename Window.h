#ifndef WINDOW_H
#define WINDOW_H

class Window
{
	public:
		Window(char* window_title, const unsigned & window_width, const unsigned & window_height);
		~Window();
		
		int getWidth();
		int getHeight();
		SDL_Surface* getSurface();
		
		SDL_Renderer* getRenderer() { return renderer_; };
	private:
		void update();
		SDL_Window* window_;
		SDL_Renderer* renderer_;
};

#endif