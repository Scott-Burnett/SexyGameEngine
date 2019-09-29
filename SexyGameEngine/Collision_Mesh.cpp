#include "Entity.h"
#include "fstream"
//#include <SDL_image.h>
#include <iostream>

Collision_Mesh::Collision_Mesh() {
}

Collision_Mesh::Collision_Mesh(int down_scale, Entity *entity)
{
	this->_entity = entity;

	_w = _entity->w();
	_h = _entity->h();
	_down_scale = down_scale;
	_w_scaled = _w / _down_scale;
	_h_scaled = _h / _down_scale;

	_mesh = new Mesh[_entity->num_states()];

	SDL_PixelFormat *pixel_format;
	int bpp, length;
	Uint8 *p;
	Uint32 pixel;
	Uint8 r, g, b, a;

	// create cmv file from png
	for (int i = 0; i < _entity->num_states(); i++) {
		// Open file
		std::ofstream cmv_out;
		cmv_out.open(_entity->_root_dir + "/Mesh/" + _entity->file_name(i) + ".cmv");

		// Create surface from png
		SDL_Surface *surface = IMG_Load((_entity->_root_dir + "/Mesh/Images/" + _entity->file_name(i) + ".png").c_str());
		if (!surface) std::cerr << "Failed to create surface: " <<  std::endl;

		pixel_format = surface->format;
		bpp = pixel_format->BytesPerPixel;
		length = surface->w * surface->h;

		for (int k = 0; k < length; k += bpp) {
			p = (Uint8*)surface->pixels + k;
			switch (bpp) {
			case 1:
				pixel = *p;
				break;
			case 2:
				pixel = *(Uint16*)p;
				break;
			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					pixel = p[0] << 16 | p[1] << 8 | p[2];
				else
					pixel = p[0] | p[1] << 8 | p[2] << 16;
				break;
			case 4:
				pixel = *(Uint32*)p;
				break;
			default:
				pixel = *(Uint32*)p;
				break;
			}
			SDL_GetRGBA(pixel, pixel_format, &r, &g, &b, &a);
			cmv_out << (a > 0) ? 0 : 1;
		}
		cmv_out.close();
		SDL_FreeSurface(surface);
	}

	// read from cmv file
	for (int i = 0, length = 0; i < _entity->num_states(); i++) {
		std::ifstream cmv_in(_entity->_root_dir + "/Mesh/" + _entity->file_name(i) + ".cmv");
		while (cmv_in.get() != EOF) length++;
		cmv_in.clear();
		cmv_in.seekg(0, std::ios::beg);

		_mesh[i] = { new bool[length], length / _h_scaled / _w_scaled };

		for (int k = 0; k < length; k++)
			_mesh[i]._matrix[k] = cmv_in.get() == 1;

		cmv_in.close();
	}
}

Collision_Mesh::~Collision_Mesh() {
}



bool Collision_Mesh::intersects(Collision_Mesh *other) {
	int _x = this->x();
	int _y = this->y();

	int other_x = other->x();
	int other_y = other->y();

	//Check for AABB Intersection
	if (_y + _h > other_y)
		return false;
	if (other_y + other->h() > _y)
		return false;
	if (_x > other_x + other->w())
		return false;
	if (other_x > _x + _w)
		return false;

	//Px Intersection
	int start_x, start_y, 
		start_other_x, start_other_y,
		overlap_w, overlap_h;

	if (other_x < _x) {
		start_other_x = _x - other_x;
		start_x = 0;
		overlap_w = other->w() - start_other_x;
	}
	else {
		start_x = other_x - _x;
		start_other_x = 0;
		overlap_w = _w - start_x;
	}
	if (other_y < _y) {
		start_other_y = _y - other_y;
		start_y = 0;
		overlap_h = other->h() - start_other_y;
	}
	else {
		start_y = other_y - _y;
		start_other_y = 0;
		overlap_h = _h - start_y;
	}

	int pos = start_y * curr_length() + frame_counter() * _w + start_x;
	int pos_other = start_other_y * other->curr_length() + other->frame_counter() * other->w() + start_other_x;

	int scale = _down_scale, scale_other = other->_down_scale;
	int step = (scale > scale_other) ? scale : scale_other;
	int overstep = (overlap_w % step == 0) ? overlap_w : (((overlap_w / step) + 1) * step);

	int wrap_around = (step * curr_length()) - overstep;
	int wrap_around_other = (step  * other->curr_length()) - overstep; 

	for (int y = 0; y < overlap_h; y += step, pos += wrap_around, pos_other += wrap_around_other)
		for (int x = 0; x < overlap_w; x += step, pos += step, pos_other += step)
			if (at(pos / scale) && other->at(pos_other / scale_other))
				return true;

	return false;
}

bool Collision_Mesh::intersects_AABB(Collision_Mesh *other) {
	int _x = this->x();
	int _y = this->y();

	int other_x = other->x();
	int other_y = other->y();

	if (_y + _h > other_y)
		return false;
	if (other_y + other->h() > _y)
		return false;
	if (_x > other_x + other->w())
		return false;
	if (other_x > _x + _w)
		return false;

	return true;
}

inline int Collision_Mesh::x() { return _entity->x(); }
inline int Collision_Mesh::y() { return _entity->y(); }
inline int Collision_Mesh::w() { return _entity->w(); }
inline int Collision_Mesh::h() { return _entity->h(); }
inline int Collision_Mesh::frame_counter() { return _entity->frame_counter(); }
inline int Collision_Mesh::curr_length() { return _entity->curr_frames() * _w_scaled; }
inline Collision_Mesh::Mesh Collision_Mesh::curr_mesh() { return _mesh[_entity->state()]; }
inline bool Collision_Mesh::at(int index) { return _mesh[_entity->state()]._matrix[index]; }
