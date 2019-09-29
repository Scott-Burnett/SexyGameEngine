#include "Entity.h"

/*-------------------------- Component --------------------------*/
Component::Component() {
}

Component::~Component() {
}

void Component::linkEntity(Entity *entity) {
	this->_entity = entity;
}
// Component

/*--------------------------- Entity ---------------------------*/
Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::update() {
}

void Entity::draw() {
}

bool Entity::intersects(Entity* other) {
	return false;
}

void Entity::linkComponents() {
}

void Entity::proceedWithState() {
	_frame_counter = ((SDL_GetTicks() - _start_time) * _fps / 1000) % _curr_frames;
}

void Entity::newState(int new_state) {
	_state = new_state;
	_curr_frames = _states[_state].frames();
	_frame_counter = 0;
	_start_time = SDL_GetTicks();
}

// Entity