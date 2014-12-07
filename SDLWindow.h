#ifndef SDLWINDOW_H
#define SDLWINDOW_H

class SDLWindow
{
	public:
		SDLWindow(char* window_title, const unsigned & window_width, const unsigned & window_height);
		~SDLWindow() {	SDL_DestroyWindow(window_); };
		const unsigned get_height(){return window_height_;}
		const unsigned get_width(){return window_width_;}		
		SDL_Renderer* getRenderer() { return renderer_; };
	private:
		char* window_title_;
		unsigned window_width_;
		unsigned window_height_;
		void update();
		SDL_Window* window_;
		SDL_Renderer* renderer_;
};

#endif