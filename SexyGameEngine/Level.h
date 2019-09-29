#pragma once
#include "Entity.h"

const int
LEVEL_MESH_DOWNSCALE = 100;

const int LEVEL_NUM_STATES = 1;

static Entity::State *_level_states = new Entity::State[LEVEL_NUM_STATES]{
	Entity::State(0, 1, "Image1")
};

class Level : public Entity {
public:
	Level();
	Level(const std::string &root_dir);
	~Level();

	void draw();
	void Update();
	bool intersects(Entity *other);
	void linkComponents();

	bool at(int x, int y);

private:
	int _down_scale;
	int _num_background_elements, _num_foreground_elements;
	//Sprite *_background_elements;
	//Sprite *_platforms;
	//Sprite *_foreground_elements;
	//Collision_Mesh *_mesh;
};