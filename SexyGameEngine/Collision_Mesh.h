#pragma once
#include "Entity.h"
#include <string>

struct Mesh {
public:
	bool *_matrix;
	int _frames;	
};

class Collision_Mesh {
public:
	Collision_Mesh();
	Collision_Mesh(int down_scale, Entity *entity);
	~Collision_Mesh();

	void linkEntity(Entity *entity);
	bool intersects(Collision_Mesh other);

private:
	Entity *_entity;

	int _w, _h;
	int _w_scaled, _h_scaled;
	int _down_scale;

	Mesh *_mesh;

	bool intersects_AABB(Collision_Mesh other);

public:
	inline int x() { return _entity->x(); }
	inline int y() { return _entity->y(); }
	inline int w() { return _entity->w(); }
	inline int h() { return _entity->h(); }
	inline int frame_counter() { return _entity->frame_counter(); }
	inline int curr_length() { return _entity->curr_frames() * _w_scaled; }
	inline Mesh curr_mesh() { return _mesh[_entity->state()]; }
	inline bool at(int index) { return _mesh[_entity->state()]._matrix[index]; }
};