#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "classes.h"
#include "Window.h"
#include "Map.h"
#include "Timer.h"
#include "Entity.h"

enum ACTION
{
	QUIT_GAME,
	GAME_OVER,
	EXIT_GAME,
	NONE
};

class Play
{
	public:
		Play(unsigned height, unsigned width, Window& window);
		~Play();
		ACTION run(SDL_Event&);
		unsigned getScore() { return score_; }
	private:
		void pause() = delete;
		void readInput(SDL_Event&);
		void update();
		void render();
		
		Map map_;
		SDL_Rect camera_;
		Window window_;
		
		Timer capTimer_;
		
		TTF_Font* font_{};
		Texture text_;
		
		unsigned score_;
		ACTION action_;
		bool gameOver_;
		bool exitGame_;
};


#endif