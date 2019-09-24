#pragma once
#include "SDL.h"
#include <string>

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
};

class Entity {
public:
	Entity();
	~Entity();

	virtual void update();
	virtual void draw();
	virtual void linkComponents();

	void proceedWithState();
	void newState(int new_state);

	int _x, _y;
	int _w, _h;
	std::string _root_dir;

	State *_states;
	int _state, _num_states;
	int _frame_counter, _curr_frames;
	int _fps;
	Uint32 _start_time;

public:
	inline int x() { return _x; }
	inline int y() { return _y; } 
	inline int w() { return _w; }
	inline int h() { return _h; }
	inline const std::string root_dir() { return _root_dir; }
	inline std::string file_name(int state) { return _states[state].file_name(); }
	inline int state() { return _state; }
	inline int num_states() { return _num_states; }
	inline int frame_counter() { return _frame_counter; }
	inline int curr_frames() { return _curr_frames; }
};