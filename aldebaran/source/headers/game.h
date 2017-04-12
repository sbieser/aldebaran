#ifndef GAME_H
#define GAME_H

class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void gameloop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);
};

#endif // !GAME_H
