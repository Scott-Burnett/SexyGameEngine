#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "Collision_Mesh.h"

const int
LEVEL_MESH_DOWNSCALE = 100;

class Level : public Entity {
public:
	Level();
	Level(const std::string &root_dir);
	~Level();
	bool at(int x, int y);
	void draw();
	void Update();
	void linkComponents();

	bool intersects(Entity *other);

private:
	int _down_scale = LEVEL_MESH_DOWNSCALE;
	int _num_background_elements, _num_foreground_elements;
	Sprite *_background_elements;
	Sprite _platforms;
	Sprite *_foreground_elements;
	Collision_Mesh _mesh;
};