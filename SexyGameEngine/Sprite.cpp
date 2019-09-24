#include "Sprite.h"
#include "Game.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

Sprite::Sprite() {
}

Sprite::Sprite(Entity *entity, int img_w, int img_h) :
_img_w(img_w), _img_h(img_h)
{
	this->_entity = entity;
	_state = _entity->_state;
	_num_states = _entity->_num_states;
	animations = new Animation[_entity->_num_states];
	src = SDL_Rect { 0, 0, _img_w, _img_h };
	dest = SDL_Rect { _entity->_x, _entity->_y, _entity->_w, _entity->_h};

	for (int i = 0; i < _entity->_num_states; i++)
		animations[i] = Animation(_img_w, _img_h, _entity->_root_dir + "/Animations/" + _entity->file_name(i) + ".png");

	_curr = animations[_state].get();
	_curr_frames = animations[_state]._frames;	
}

Sprite::~Sprite() {
}

void Sprite::draw() {

	dest.x = _entity->_x;
	dest.y = _entity->_y;
	if (_entity->_state != _state) {
		_state = _entity->_state;
		_curr = animations[_state].get();
		_curr_frames = animations[_state]._frames;
	}

	src.x = _img_w * _entity->frame_counter();
	SDL_RenderCopy(Game::_window._renderer, _curr, &src, &dest);
}

void Sprite::linkEntity(Entity *entity) {
	this->_entity = entity;
}