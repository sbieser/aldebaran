#include "input.h"

/*
	input.cpp implementation

	Keeps track of keyboard state
*/

//this function gets called at the beginning of each new frame
//to reset the keys that are no longer relevant
void Input::beginNewFrame() {
	this->_pressedKeys.clear();
	this->_relesedKeys.clear();
}

//This gets called when a key is released
void Input::keyUpEvent(const SDL_Event & event) {
	this->_relesedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;
}

//This gets called when a key has been pressed
void Input::keyDownEvent(const SDL_Event & event) {
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}

//Check if certain key was pressed during current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->_pressedKeys[key];
}

//Check if certain key was released during current frame
bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->_relesedKeys[key];
}

//Check if certain key is currently held during current frame
bool Input::isKeyHeld(SDL_Scancode key) {
	return this->_heldKeys[key];
}
