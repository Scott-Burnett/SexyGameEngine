#include "Level.h"

Level::Level() {
}

Level::Level(const std::string &root_dir) {
	_x = 0;
	_y = 0;
	_w = 1000;
	_h = 1000;
	_num_states = 1;
	_frame_counter = 0;
	_curr_frames = 1;

	_root_dir = root_dir;
	_mesh = Collision_Mesh(_down_scale, this);
}

Level::~Level() {
}

bool Level::at(int x, int y) {
	return _mesh.at((y * _w + x) / _down_scale);
}

void Level::draw() {

}

void Level::Update() {

}

void Level::linkComponents() {

}

bool Level::intersects(Entity *other) {
	
}