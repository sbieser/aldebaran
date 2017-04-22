#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "globals.h"
#include "sprite.h"
#include <map>
#include <string>
#include <vector>

class Graphics;

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
	/// <param name="sourceX">The source x.</param>
	/// <param name="sourceY">The source y.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <param name="posX">The position x.</param>
	/// <param name="y">The y.</param>
	/// <param name="scale">The scale.</param>
	/// <param name="timeToUpdate">The time to update.</param>
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float scale, float timeToUpdate);
	
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
	/// Draws the specified graphics.
	/// </summary>
	/// <param name="graphics">The graphics.</param>
	void draw(Graphics &graphics /*, int x, int y*/);

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
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);


protected:
	double _timeToUpdate;
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
	
	/// <summary>
	/// For sprite sheets where offset is needed to specify where the
	/// actual image is
	/// </summary>
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
};


#endif // !ANIMATED_SPRITE_H
