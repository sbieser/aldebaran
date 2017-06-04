#ifndef  TILED_FRAME_H
#define TILED_FRAME_H

class Tiled_Tile;

class Tiled_Frame {
public:
	Tiled_Frame(Tiled_Tile * tile, int duration);
	~Tiled_Frame();
	int _duration;
	Tiled_Tile* _tile;
protected:
private:
	//Tiled_Tile* _tile;
};
#endif // ! TILED_FRAME_H
