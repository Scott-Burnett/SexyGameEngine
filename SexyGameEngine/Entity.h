#ifndef ENTITY_H
#define ENTITY_H

#include "../dependencies/include/SDL.h"
#include "../dependencies/include/SDL_image.h"
#include "Vector2D.h"
#include <string>


enum ComponentID {
	SPRITE_COMPONENT, 
	MESH_COMPONENT
};

// Forward declarations
class Component;
class Entity;

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Components %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
class Component {
public:
	Component();
	~Component();

	Entity *_entity;
	void linkEntity(Entity *entity);
}; // Class Component

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Collision_Mesh ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
class Collision_Mesh : public Component {
public:
	enum Edge {
		Right,
		Bottom,
		Left,
		Top,
		None
	};

	struct Mesh {
	public:
		bool *_matrix;
		int _frames;
		Mesh();
		Mesh(int w_scaled, int h_scaled, const std::string dir);
		~Mesh();
	};

	Collision_Mesh();
	Collision_Mesh(Entity *entity, int down_scale);
	Collision_Mesh(Entity *entity, int down_scale, Mesh *mesh);
	~Collision_Mesh();

	Edge intersectEdge(Collision_Mesh *other);
	Vector2D intersect(Collision_Mesh *other);
	bool intersects_AABB(Collision_Mesh *other);

	void print();

private:
	int _w, _h;
	int _w_scaled, _h_scaled;
	int _down_scale;

	Mesh *_mesh;

public:
	inline int x();
	inline int y();
	inline int v_x();
	inline int v_y();
	inline int w();
	inline int h();
	inline int frame_counter();
	inline int curr_length();
	inline Mesh curr_mesh();
	inline bool at(int index);
}; // Component Collision_Mesh

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Sprite ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
class Sprite : public Component {
public:

	static struct Animation {
	public:
		SDL_Texture *_texture;
		int _frames;
		int _w, _h;

		Animation();
		Animation(int w, int h, const std::string &path);
		~Animation();

		SDL_Texture* get();
	};

	Sprite();
	Sprite(Entity *entity, int img_w, int img_h);
	Sprite(Entity *entity, int img_w, int img_h, Animation *anims);
	~Sprite();

	void draw();

private:
	int _img_w, _img_h;

	int _state, _num_states;
	int _curr_frames;
	SDL_Rect src, dest;
	SDL_Texture *_curr;
	Animation *animations;
}; // Component Sprite

/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Entity %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
/* :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */

class Entity {
public:

	struct State {
	private:
		int _type, _frames;
		std::string _file_name;
	public:
		State() {}
		State(int type, int frames, std::string file_name) :
			_type(type), _frames(frames), _file_name(file_name) {}
		inline int type() { return _type; }
		inline int frames() { return _frames; }
		inline std::string file_name() { return _file_name; }
	}; // Struct State

	std::string _root_dir;
	int _x, _y;
	int _v_x, _v_y;
	int _w, _h;

	State *_states;
	int _state, _num_states;
	int _frame_counter, _curr_frames;
	int _fps;
	Uint32 _start_time;

	// Components
	Sprite *_sprite;
	Collision_Mesh *_mesh;

	Entity();
	~Entity();

	void linkComponents();
	void holdFrame();
	void proceedWithState();
	void newState(int new_state);
	void applyVelocity();
	
	virtual void update();
	virtual void draw();

	virtual Collision_Mesh::Edge intersectEdge(Entity *other);
	virtual Vector2D intersect(Entity *other);
	virtual Vector2D displace(Vector2D location, Collision_Mesh::Edge edge);

	inline int x() { return _x; }
	inline int y() { return _y; }
	inline int v_x() { return _v_x; }
	inline int v_y() { return _v_y; }
	inline int w() { return _w; }
	inline int h() { return _h; }
	inline const std::string root_dir() { return _root_dir; }
	inline std::string file_name(int state) { return _states[state].file_name(); }
	inline int state() { return _state; }
	inline int num_states() { return _num_states; }
	inline int frame_counter() { return _frame_counter; }
	inline int curr_frames() { return _curr_frames; }
}; // Class Entity

#endif