#include "Tile.h"

Tile::Tile() {
}

Tile::Tile(int x, int y, Type type) {
	_x = x;
	_y = y;
	_v_x = 0;
	_v_y = 0;
	_w = TILE_LENGTH;
	_h = TILE_LENGTH;

	_state = 0;
	_num_states = 1;
	_states = &_tile_states[(int) type];
	_frame_counter = 0;
	_curr_frames = &_states[(int) type].frames;
	
	_type = type;

}



Tile::~Tile() {
}