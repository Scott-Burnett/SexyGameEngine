#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"

class Level {
public:
	struct TileMap {
		Tile *_matrix;
		int _tileCount;
		int _w;
		int _h;

		TileMap();
		TileMap(const std::string &dir);
		~TileMap();

		Tile *get(int x, int y);
		void draw();
	};
	Level();
	Level(const std::string &root_dir);
	~Level();

	std::string _root_dir;
	int _x, _y;
	int _w, _h;

	TileMap *_tiles;

	void collideEntities(Entity *a, Entity *b);
	void collideWith(Entity *other);

	void draw();
	void Update();

	bool at(int x, int y);

private:

};

#endif