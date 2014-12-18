#include "Game.h"
#include "SDL.h"
#include <iostream>

Game::Game(Window& window) : window_{window}, play_{nullptr}, menu_{nullptr}, submit_{nullptr}, edit_{nullptr}
{
	scoreFile_ = "score.txt";
	mapFile_ = "map.txt";
}

bool Game::run()
{
	while( !quit_ )
	{
		menu();
	}
}

void Game::menu()
{
	if( menu_ != nullptr )
	{
		delete menu_;
		menu_ = nullptr;
	}

	menu_ = new Menu{window_};

	BUTTON_CODE choice = menu_->run(e);

	switch( choice )
	{
		case BUTTON_PLAY:
			play();
			break;
			
		case BUTTON_MAP_EDITOR:
			editor();
			break;
			
		case BUTTON_SCORE:
			break;
			
		case BUTTON_CREDITS:
			break;
			
		case BUTTON_QUIT:
			quit_ = true;
			break;
			
		default:
			break;
	}
}

void Game::play()
{
	if( play_ != nullptr )
	{
		delete play_;
		play_ = nullptr;
	}

	play_ = new Play{3000,3000,window_};
	quit_ = play_->run(e);
	
	if( !quit_ )
	{
		submit();
	}
}

void Game::editor()
{
	if( edit_ != nullptr )
	{
		delete edit_;
		edit_ = nullptr;
	}
	
	edit_ = new Edit{ 3000, 3000, window_ };
	
	edit_->run(e);
}


void Game::submit()
{
	if( submit_ != nullptr )
	{
		delete submit_;
		submit_ = nullptr;
	}

	submit_= new Submit{ window_ };

	switch( submit_->run(e) )
	{
		case BUTTON_SUBMIT:
			saveScore(play_->getScore(), submit_->getNick());
			break;
		
		case BUTTON_QUIT:
			quit_ = true;
			break;
	}
}

void Game::saveScore(const unsigned & score, const std::string & nick)
{
	std::ifstream ifs(scoreFile_);
	std::string str;
	unsigned un;
	std::multimap<unsigned, std::string> themap;
	
	while(ifs>>str>>un)
	{
		themap.insert(std::pair<unsigned, std::string>(un,str));
	}
	ifs.close();
	
	if(nick.size()==0)
		str="Unknown";
	else 
		str=nick;
	
	themap.insert(std::pair<unsigned, std::string>(score,str));
	if(themap.size()>10)
	{
		themap.erase(themap.begin());
	}

	std::ofstream ofs(scoreFile_);
	for (auto it = themap.rbegin(); it != themap.rend(); ++it)
	{
		ofs<<(*it).second << " " << (*it).first << std::endl;
	}

	ofs.close();
}