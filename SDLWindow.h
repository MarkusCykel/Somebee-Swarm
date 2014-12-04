#ifndef SDLWINDOW_H
#define SDLWINDOW_H

class SDLWindow
{
	public:
		SDLWindow(char* window_title, const unsigned & window_width, const unsigned & window_height);
		~SDLWindow() {	SDL_DestroyWindow(window_); };
		
		
		SDL_Renderer* getRenderer() { return renderer_; };
	private:
		void update();
		SDL_Window* window_;
		SDL_Renderer* renderer_;
};

#endif