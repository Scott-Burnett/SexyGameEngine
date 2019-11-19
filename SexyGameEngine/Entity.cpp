#include "Entity.h"

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Component %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
Component::Component() {
}

Component::~Component() {
}

void Component::linkEntity(Entity *entity) {
	this->_entity = entity;
}
// Component

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Entity %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::linkComponents() {
	if (_sprite)
		_sprite->linkEntity(this);
	if(_mesh)
		_mesh->linkEntity(this);
}

void Entity::holdFrame() {

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

void Entity::applyVelocity() {
	_x += _v_x;
	_y += _v_y;
	_v_x = 0;
	_v_y = 0;
}

void Entity::update() {
}

void Entity::draw() {
}

Collision_Mesh::Edge Entity::intersectEdge(Entity *other) {
	float ax = (float) other->_x;
    float ay = (float) other->_y;
    float aw = (float) other->_w;
    float ah = (float) other->_h;
    float avx = (float) other->_v_x;
    float avy = (float) other->_v_y;
    float bx = (float) this->_x;
    float by = (float) this->_y;
    float bw = (float) this->_w;
    float bh = (float) this->_h;
    float bvx = (float) this->_v_x;
    float bvy = (float) this->_v_y;

    float dy = 0.0;
    float dx = 0.0;
    float dright =0.0;
    float dleft = 0.0;
    float dtop = 0.0; 
    float dbottom = 0.0;
    
    float xmin = 0.0; 
    float xmax = 0.0; 
    float ymin = 0.0; 
    float ymax = 0.0;

    float fy = 0.0;
    float fx = 0.0;

    float iy = 0.0;
    float ix = 0.0;

    Collision_Mesh::Edge yEdge = Collision_Mesh::None;
    Collision_Mesh::Edge xEdge = Collision_Mesh::None;

    dright = bx + bw - ax;
    dleft = bx - (ax + aw);
    dtop = by - (ay + ah);
    dbottom = by + bh - ay;

    if (dright < dleft) {
        xmin = dright;
        xmax = dleft;
    }
    else {
        xmin = dleft;
        xmax = dright;
    }

    if (dtop < dbottom) {
        ymin = dtop;
        ymax = dbottom;
    }
    else {
        ymin = dbottom;
        ymax = dtop;
    }

    if (dright < 0) {
        if (dright < avx)
            return Collision_Mesh::None;
        dx = dright;
        xEdge = Collision_Mesh::Right;
    }
    else if (dleft > 0) {
        if (dleft > avx)
            return Collision_Mesh::None;
        dx = dleft;
        xEdge = Collision_Mesh::Left;
    }

    if (dtop > 0) {
        if (dtop > avy)
            return Collision_Mesh::None;
        dy = dtop;
        yEdge = Collision_Mesh::Top;
    }
    else if (dbottom < 0) {
        if (dbottom < avy)
            return Collision_Mesh::None;
        dy = dbottom;
        yEdge = Collision_Mesh::Bottom;
    } 

	fy = avy ? dy / avy : 1;
	fx = avx ? dx / avx : 1;

    iy = (fy * avx);
    ix = (fx * avy);

    if (iy >= xmin && iy <= xmax)
        return yEdge;

    if (ix >= ymin && ix <= ymax)
        return xEdge;
    
    return Collision_Mesh::None;
}

Vector2D Entity::intersect(Entity* other) {
	Collision_Mesh *other_mesh = other->_mesh;
	if (!this->_mesh || !other_mesh)
		return {-1, -1};
	return this->_mesh->intersect(other_mesh);
}

Vector2D Entity::displace(Vector2D location, Collision_Mesh::Edge edge) {
    int dy = 0, dx = 0;
	switch (edge) {
    case Collision_Mesh::Top:
        dy = this->_y - location.y;
        break;
    case Collision_Mesh::Bottom:
        dy = this->_y + this->_h - location.y;
        break;
    case Collision_Mesh::Left:
        dx = this->_x - location.x;
        break;
    case Collision_Mesh::Right:
        dx = this->_x + this->_w - location.x;
        break;
    case Collision_Mesh::None:
        break;
    default:
        break;
    }
    
    return {dx, dy};
}
// Entity