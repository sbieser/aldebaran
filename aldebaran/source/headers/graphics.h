#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <map>

struct SDL_Surface;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

/// <summary>
/// Holds all the information for dealing with graphics for the game
/// </summary>
class Graphics {
public:
	Graphics();
	~Graphics();
	
	/// <summary>
	/// Loads an image into the _spriteSheets map if it doesn't already exist.
	/// As a result, each image will only be loaded once. 
	/// </summary>
	/// <param name="filePath">The file path.</param>
	/// <returns>
	/// Returns the image from the map regardless of whether or not it 
	/// was just loaded.
	/// </returns>
	SDL_Surface* loadImage(const std::string &filePath);
	
	/// <summary>
	/// Draws a texture to a certain part of the screen. 
	/// The source texture is the source of the image, the source rectangle
	/// is the rectangle of the source image we want to render. Finally, the
	/// destination rectagnle is where we draw the source rectangle in the
	/// renderer.
	/// </summary>
	/// <param name="sourceTexture">The source texture.</param>
	/// <param name="sourceReactangle">The source reactangle.</param>
	/// <param name="destinationRectangle">The destination rectangle.</param>
	void blitSurface(SDL_Texture* sourceTexture, SDL_Rect* sourceReactangle, SDL_Rect* destinationRectangle);
	
	/// <summary>
	/// Renders everything to the screen
	/// </summary>
	void flip();
	
	/// <summary>
	/// Clears the screen
	/// </summary>
	void clear();
	
	/// <summary>
	/// Gets the renderer.
	/// </summary>
	/// <returns></returns>
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;	
	
	/// <summary>
	/// The sprite sheets
	/// </summary>
	std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif // !GRAPHICS_H
