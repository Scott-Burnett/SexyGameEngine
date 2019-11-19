#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

const std::string PLAYER_ROOT_DIR = "Resources/Player";

const int
PLAYER_HEIGHT = 120,
PLAYER_WIDTH = 120;

const int
// Player Attributes
PLAYER_MOVE_SPEED = 10,
PLAYER_FPS = 6;

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
DEAD = 23,

PLAYER_NUM_STATES = 24;
// States

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

static Sprite::Animation *PLAYER_ANIMATIONS = new Sprite::Animation[PLAYER_NUM_STATES] {
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "idle_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "idle_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "run_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "run_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "jump_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "jump_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_down_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_down.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_down_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_up_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_up.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dash_up_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "slide_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "slide_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "fall_right.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "fall_left.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "attack_light.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "attack_heavy.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "use_item.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "in_menue.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "resting.png"),
	Sprite::Animation::Animation(30, 30, PLAYER_ROOT_DIR + "/Animations/" + "dead.png")
};

static Collision_Mesh::Mesh *PLAYER_MESH = new Collision_Mesh::Mesh[PLAYER_NUM_STATES] {
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "idle_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "idle_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "run_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "run_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "jump_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "jump_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_down_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_down.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_down_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_up_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_up.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dash_up_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "slide_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "slide_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "fall_right.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "fall_left.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "attack_light.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "attack_heavy.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "use_item.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "in_menue.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "resting.cmv"),
	Collision_Mesh::Mesh::Mesh(30, 30, PLAYER_ROOT_DIR + "/Mesh/" + "dead.cmv")
};

class Player : public Entity {
public:
	Player(int x, int y, int w, int h);
	Player();
	~Player();

	void draw();
	void Update();

	int _direction;
};

#endif