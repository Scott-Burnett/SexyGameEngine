#include "Level.h"

Level::Level() {
}

Level::Level(const std::string &root_dir) {
	_x = 0;
	_y = 0;
	_w = 1000;
	_h = 1000;
	_state = 0;
	_num_states = LEVEL_NUM_STATES;
	_states = _level_states;
	_frame_counter = 0;
	_curr_frames = 1;

	int _down_scale = LEVEL_MESH_DOWNSCALE;

	_root_dir = root_dir;
	_mesh = new Collision_Mesh(_down_scale, this);
	_sprite = new Sprite(this, _w / _down_scale, _h / _down_scale);
}

Level::~Level() {
}

bool Level::at(int x, int y) {
	return _mesh->at((y * _w + x) / _down_scale);
}

void Level::draw() {
	_sprite->draw();
	//std::cout << "Level:" << std::endl;
	//_mesh->print();
}

void Level::Update() {

}

void Level::linkComponents() {
	_mesh->linkEntity(this);
}
