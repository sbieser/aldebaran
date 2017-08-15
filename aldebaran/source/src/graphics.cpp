#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "globals.h"
/**
	
	Graphics Class

	Holds all the information for dealing with graphics for the game

*/

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Aldeberan");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
	if (this->_spriteSheets.count(filePath) == 0) {
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* sourceTexture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	//SDL_Log("%i,%i\n", destinationRectangle->x, destinationRectangle->y);
	SDL_RenderCopy(this->_renderer, sourceTexture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}
