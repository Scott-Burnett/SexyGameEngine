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

Vector2D Entity::intersects(Entity* other) {
	Collision_Mesh *other_mesh = other->_mesh;
	if (!other_mesh)
		return Vector2D(0,0);
	return this->_mesh->intersects(other_mesh);
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