#ifndef TILE_H
#define TILE_H
#include "Entity.h"

const std::string TILE_ROOT_DIR = "Resources/Tiles";

// Tile Types Enumeration
enum Type {
	Empty, 
	Solid,
	Angle_TL,
	Angle_TR,
	Angle_BL,
	Angle_BR,
	Corner_TL,
	Corner_TR,
	Arch_TL,
	Arch_TR,
	Arch,
	Stair_L,
	Star_R,
	Door
};

const int
TILE_LENGTH = 100,
TILE_NUM_TYPES = 14;

static Entity::State *_tile_states = new Entity::State[TILE_NUM_TYPES] {
	Entity::State(0, 1, "Empty"),
	Entity::State(0, 1, "Solid"),
	Entity::State(0, 1, "Angle_TL"),
	Entity::State(0, 1, "Angle_TR"),
	Entity::State(0, 1, "Angle_BL"),
	Entity::State(0, 1, "Angle_BR"),
	Entity::State(0, 1, "Corner_TL"),
	Entity::State(0, 1, "Corner_TR"),
	Entity::State(0, 1, "Arch_TL"),
	Entity::State(0, 1, "Arch_TR"),
	Entity::State(0, 1, "Arch"),
	Entity::State(0, 1, "Stair_L"),
	Entity::State(0, 1, "Stair_R"),
	Entity::State(0, 1, "Door")
};

class Tile : public Entity {
public:

	Tile();
	Tile(int x, int y, Type type);
	~Tile();

	Type _type;
};

#endif