#include <SDL.h>
#include "graphics.h"

/**
	
	Graphics Class

	Holds all the information for dealing with graphics for the game

*/

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Aldeberan");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
}

