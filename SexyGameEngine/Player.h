#pragma once
#include "Entity.h"

const std::string PLAYER_ROOT_DIR = "Resources/Player";

const int
PLAYER_NUM_STATES = 24,
PLAYER_H = 120,
PLAYER_W = 120;

const int
//States Enumeration
IDLE_RIGHT = 0,
IDLE_LEFT = 1,
RUN_RIGHT = 2,
RUN_LEFT = 3,
JUMP_RIGHT = 4,
JUMP_LEFT = 5,
DASH_RIGHT = 6,
DASH_DOWN_RIGHT = 7,
DASH_DOWN = 8,
DASH_DOWN_LEFT = 9,
DASH_LEFT = 10,
DASH_UP_LEFT = 11,
DASH_UP = 12,
DASH_UP_RIGHT = 13,
SLIDE_RIGHT = 14,
SLIDE_LEFT = 15,
FALL_RIGHT = 16,
FALL_LEFT = 17,
ATTACK_LIGHT = 18,
ATTACK_HEAVY = 19,
USE_ITEM = 20,
IN_MENUE = 21,
RESTING = 22,
DEAD = 23;

static Entity::State *_player_states = new Entity::State[PLAYER_NUM_STATES]{
	Entity::State(IDLE_RIGHT, 8, "idle_right"),
	Entity::State(IDLE_LEFT, 8, "idle_left"),
	Entity::State(RUN_RIGHT, 8, "run_right"),
	Entity::State(RUN_LEFT, 8, "run_left"),
	Entity::State(JUMP_RIGHT, 8, "jump_right"),
	Entity::State(JUMP_LEFT, 8, "jump_left"),
	Entity::State(DASH_RIGHT, 8, "dash_right"),
	Entity::State(DASH_DOWN_RIGHT, 8, "dash_down_right"),
	Entity::State(DASH_DOWN, 8, "dash_down"),
	Entity::State(DASH_DOWN_LEFT, 8, "dash_down_left"),
	Entity::State(DASH_LEFT, 8, "dash_left"),
	Entity::State(DASH_UP_LEFT, 8, "dash_up_left"),
	Entity::State(DASH_UP, 8, "dash_up"),
	Entity::State(DASH_UP_RIGHT, 8, "dash_up_right"),
	Entity::State(SLIDE_RIGHT, 8, "slide_right"),
	Entity::State(SLIDE_LEFT, 8, "slide_left"),
	Entity::State(FALL_RIGHT, 8, "fall_right"),
	Entity::State(FALL_LEFT, 8, "fall_left"),
	Entity::State(ATTACK_LIGHT, 8, "attack_light"),
	Entity::State(ATTACK_HEAVY, 8, "attack_heavy"),
	Entity::State(USE_ITEM, 8, "use_item"),
	Entity::State(IN_MENUE, 8, "in_menue"),
	Entity::State(RESTING, 8, "resting"),
	Entity::State(DEAD, 8, "dead")
};

const int
PLAYER_FPS = 6;

class Player : public Entity {
public:
	Player(int x, int y, int w, int h);
	Player();
	~Player();

	void draw();
	void Update();
	void linkComponents();

	int _direction;
};
