#ifndef HIGHSCORE_H
#define HIGHSCORE_H

class HighScore
{
	public:
		Menu(Window& window);
		~Menu();
		SELECTION run(SDL_Event&);
	private:
		void readInput(SDL_Event&);
		void update();
		void render(); 
		
		Window window_;
		std::vector<Button*> buttons_;
		Texture background_;
		
		SELECTION selection_{GAME};
		bool selected_{false};
		
};

#endif