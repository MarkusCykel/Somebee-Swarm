#ifndef MAPEDITWINDOW_H
#define MAPEDITWINDOW_H

class MapEditWindow
{
	public:
		MapEditWindow(char* window_title, const unsigned & window_width, const unsigned & window_height);
		~MapEditWindow() {	SDL_DestroyWindow(window_); };
		
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