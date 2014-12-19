#include "Texture.h"

Texture::Texture()
{
	//Initialize
	texture_ = NULL;
	width_ = 0;
	height_ = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile( SDL_Renderer* renderer, std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		std::cout<< "Unable to load image %s! SDL_image Error: %s\n" << path.c_str() << IMG_GetError() << std::endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			std::cout<< "Unable to create texture from %s! SDL Error: %s\n" << path.c_str() << IMG_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			width_ = loadedSurface->w;
			height_ = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	texture_ = newTexture;
	return texture_ != NULL;
}

bool Texture::loadFromFileStretched( SDL_Renderer* renderer, std::string path, unsigned width, unsigned height )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	SDL_Surface* stretchedSurface = SDL_CreateRGBSurface(0,width, height,32,0,0,0,0);
	
	if( loadedSurface == NULL )
	{
		std::cout << "Unable to load image %s! SDL_image Error: %s\n"<< path.c_str() << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_BlitScaled( loadedSurface, NULL , stretchedSurface, NULL);
		
		//Color key image
		SDL_SetColorKey( stretchedSurface, SDL_TRUE, SDL_MapRGB( stretchedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, stretchedSurface );
		if( newTexture == NULL )
		{
			std::cout << "Unable to create texture from %s! SDL Error: %s\n"<< path.c_str() << IMG_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			width_ = stretchedSurface->w;
			height_ = stretchedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
		SDL_FreeSurface( stretchedSurface );
	}

	//Return success
	texture_ = newTexture;
	return texture_ != NULL;
}

bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer )
{
	//Get rid of preexisting texture
	free();
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: %s\n" << SDL_GetError() << std::endl;
	}
	else
	{
		//Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texture_ == NULL )
		{
			std::cout << "Unable to create texture from rendered text! SDL Error: %s\n" << SDL_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			width_ = textSurface->w;
			height_ = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
	//Return success
	return texture_ != NULL;
}

void Texture::free()
{
	//Free texture if it exists
	if( texture_ != NULL )
	{
		SDL_DestroyTexture( texture_ );
		texture_ = NULL;
		width_ = 0;
		height_ = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( texture_, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( texture_, blending );
}
		
void Texture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( texture_, alpha );
}

void Texture::render( SDL_Renderer* renderer, SDL_Rect* srcrect, SDL_Rect* dstrect, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Render to screen
	SDL_RenderCopyEx( renderer, texture_, srcrect, dstrect, angle, center, flip );
}