#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "globals.h"
#include "sprite.h"
#include <map>
#include <string>
#include <vector>

class Graphics;
struct SDL_Rect;

/// <summary>
/// TODO: When playing an animation just once, loops on update and draw occur, even after the animation has finished. Is there a better solution?
/// TODO: Still not sure what offset does?
/// </summary>
/// <seealso cref="Sprite" />
class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
		
	/// <summary>
	/// Initializes a new instance of the <see cref="AnimatedSprite"/> class.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	/// <param name="filePath">The file path.</param>
	/// <param name="posX">The position x.</param>
	/// <param name="posY">The position y.</param>
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int posX, int posY);

	/// <summary>
	/// Plays the animation provided if its not already playing.
	/// </summary>
	/// <param name="animation">The animation.</param>
	/// <param name="once">if set to <c>true</c> [once].</param>
	void playAnimation(std::string animation, bool once = false);

	
	/// <summary>
	/// Updates the animated sprite with a timer
	/// </summary>
	/// <param name="elapsedTime">The elapsed time.</param>
	void update(int elapsedTime);
	
	/// <summary>
	/// Determines new source rectangle and calls parents draw method
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	void draw(Graphics &graphics);

	void draw(Graphics &graphics, SDL_Rect* camera);

	/// <summary>
	/// Adds the animation to the map of animations for the sprite
	/// </summary>
	/// <param name="frames">The frames.</param>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <param name="name">The name.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <param name="offset">The offset.</param>
	void addAnimation(int frames, int x, int y, std::string name, int width, int height);

	void setTimeToUpdate(int timeToUpdate);

protected:
	//TODO: _timeToUpdate to _animationSpeed and make it integer
	int _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;
	
	
	/// <summary>
	/// Resets all animation associated with this sprite
	/// </summary>
	void resetAnimation();
	
	/// <summary>
	/// Stops the animation.
	/// </summary>
	void stopAnimation();
	
	/// <summary>
	/// Sets the visibility of the animated sprite
	/// </summary>
	/// <param name="visible">if set to <c>true</c> [visible].</param>
	void setVisible(bool visible);
	
	/// <summary>
	/// Logic that triggers at the end of an animation
	/// </summary>
	/// <param name="currentAnimation">The current animation.</param>
	virtual void animationDone(std::string currentAnimation) = 0;

	/// <summary>
	/// Setups the animation.
	/// </summary>
	virtual void setupAnimation() = 0;

private:	
	/// <summary>
	/// A list of ractangles for a label animation
	/// </summary>
	std::map<std::string, std::vector<SDL_Rect>> _animations;

	int _frameIndex;

	double _timeElapsed;
	
	bool _visible;
};


#endif // !ANIMATED_SPRITE_H
