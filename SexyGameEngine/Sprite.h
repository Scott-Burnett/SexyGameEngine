#pragma once
#include "Entity.h"
#include "Window.h"
#include "Animation.h"

class Sprite {
public:
	Sprite();
	Sprite(Entity *entity, int img_w, int img_h);
	~Sprite();

	void draw();
	void linkEntity(Entity *entity);

private:
	Entity *_entity;
	int _img_w, _img_h;

	int _state, _num_states;
	int _curr_frames;
	SDL_Rect src, dest;
	SDL_Texture *_curr;
	Animation *animations;
};