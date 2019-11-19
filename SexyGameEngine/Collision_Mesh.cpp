#include "Entity.h"
#include "fstream"
#include <iostream>

Collision_Mesh::Mesh::Mesh() {
}

Collision_Mesh::Mesh::Mesh(int w_scaled, int h_scaled, std::string path) {
	int length = 0;
	std::ifstream cmv_in(path);
	while (cmv_in.get() != EOF) length++;
	cmv_in.clear();
	cmv_in.seekg(0, std::ios::beg);

	_matrix = new bool[length];
	_frames = length / h_scaled / w_scaled;

	for (int k = 0; k < length; k++)
		_matrix[k] = (cmv_in.get() == '1');

	cmv_in.close();
}

Collision_Mesh::Mesh::~Mesh(){
}

Collision_Mesh::Collision_Mesh() {
}

Collision_Mesh::Collision_Mesh(Entity *entity, int down_scale)
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
		length = surface->w * surface->h * bpp;

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
		_mesh[i] = Mesh(_w_scaled, _h_scaled, _entity->_root_dir + "/Mesh/" + _entity->file_name(i) + ".cmv");
	}
}

Collision_Mesh::Collision_Mesh(Entity *entity, int down_scale, Mesh *mesh) {
	this->_entity = entity;

	_w = _entity->w();
	_h = _entity->h();
	_down_scale = down_scale;
	_w_scaled = _w / _down_scale;
	_h_scaled = _h / _down_scale;

	_mesh = mesh;
}

Collision_Mesh::~Collision_Mesh() {
}

Collision_Mesh::Edge Collision_Mesh::intersectEdge(Collision_Mesh *other){
	return _entity->intersectEdge(other->_entity);
}

Vector2D Collision_Mesh::intersect(Collision_Mesh *other) {
	// return Global location of px intersection with other
	int _x = this->x() + this->v_x();
	int _y = this->y() + this-> v_y();

	int other_x = other->x() + other->v_x();
	int other_y = other->y() + other->v_y();
	int other_w = other->w();
	int other_h = other->h();

	//Check for AABB Intersection
	if (_y + _h < other_y)
		return {-1,-1};
	if (other_y + other_h < _y)
		return {-1,-1};
	if (_x > other_x + other_w)
		return {-1,-1};
	if (other_x > _x + _w)
		return {-1,-1};

	//Px Intersection
	int start_x, start_y,
		start_other_x, start_other_y,
		pos, pos_other,
		overlap_w, overlap_h;

	int scale = _down_scale, scale_other = other->_down_scale;
	int step = (scale < scale_other) ? scale : scale_other;

	if (other_x < _x) {
		start_other_x = (_x - other_x);
		start_x = 0;
		overlap_w = (_x + _w < other->x() + other_w) ? _w : other_w - start_other_x;
	}
	else {
		start_x = (other_x - _x);
		start_other_x = 0;
		overlap_w = (other_x + other_w < _x + _w) ? other_w : _w - start_x;
	}
	if (other_y < _y) {
		start_other_y = (_y - other_y);
		start_y = 0;
		overlap_h = (_y + _h < other->y() + other_h) ? _h : other_h - start_other_y;
	}
	else {
		start_y = (other_y - _y);
		start_other_y = 0;
		overlap_h = (other_y + other_h < _y + _h) ? other_h : _h - start_y;
	}

	switch(other->intersectEdge(this)) {
	case Right: // return leftmost :: top->bottom, lef->right
		for (int x = 0; x < overlap_w; x += step) { 
			for (int y = 0; y < overlap_h; y += step) {
				pos = ((((start_y + y) / scale) * (curr_length() / scale)) + ((frame_counter() * _w) + start_x + x) / scale);
				pos_other = ((((start_other_y + y) / scale_other) * (other->curr_length()) / scale_other) + ((other->frame_counter() * other_w) + start_other_x + x) / scale_other);
				if ((at(pos)) && (other->at(pos_other))) {
					std::cout << "Collision: " << _x + start_x + x << ", " << _y + start_y + y << std::endl;
					return {_x + start_x + x, _y + start_y + y};
				}
			}
		}
		break;
	case Left: // return rightmost :: top->bottom, right->left
		for (int x = overlap_w - 1; x > -1; x -= step) {
			for (int y = 0; y < overlap_h; y += step) { 
				pos = ((((start_y + y) / scale) * (curr_length() / scale)) + ((frame_counter() * _w) + start_x + x) / scale);
				pos_other = ((((start_other_y + y) / scale_other) * (other->curr_length()) / scale_other) + ((other->frame_counter() * other_w) + start_other_x + x) / scale_other);
				if ((at(pos)) && (other->at(pos_other))) {
					std::cout << "Collision: " << _x + start_x + x << ", " << _y + start_y + y << std::endl;
					return {_x + start_x + x, _y + start_y + y};
				}
			}
		}
		break;
	case Bottom: // return topmost :: left->right, top->bottom
		for (int y = 0; y < overlap_h; y += step) {
			for (int x = 0; x < overlap_w; x += step) {
				pos = ((((start_y + y) / scale) * (curr_length() / scale)) + ((frame_counter() * _w) + start_x + x) / scale);
				pos_other = ((((start_other_y + y) / scale_other) * (other->curr_length()) / scale_other) + ((other->frame_counter() * other_w) + start_other_x + x) / scale_other);
				if ((at(pos)) && (other->at(pos_other))) {
					std::cout << "Collision: " << _x + start_x + x << ", " << _y + start_y + y << std::endl;
					return {_x + start_x + x, _y + start_y + y};
				}
			}
		}
		break;
	case Top: // return bottommost :: left->right, bottom->top
		for (int y = overlap_h - 1; y > -1; y -= step) {
			for (int x = 0; x < overlap_w; x += step) {
				pos = ((((start_y + y) / scale) * (curr_length() / scale)) + ((frame_counter() * _w) + start_x + x) / scale);
				pos_other = ((((start_other_y + y) / scale_other) * (other->curr_length()) / scale_other) + ((other->frame_counter() * other_w) + start_other_x + x) / scale_other);
				if ((at(pos)) && (other->at(pos_other))) {
					std::cout << "Collision: " << _x + start_x + x << ", " << _y + start_y + y << std::endl;
					return {_x + start_x + x, _y + start_y + y};
				}
			}
		}
		break;
	case None:
		return {-1, -1};
		break;
	default:
		break;
	}

	return {-1, -1};
}

bool Collision_Mesh::intersects_AABB(Collision_Mesh *other) {
	int _x = this->x() + this->v_x();
	int _y = this->y() + this-> v_y();

	int other_x = other->x() + other->v_x();
	int other_y = other->y() + other->v_y();
	int other_w = other->w();
	int other_h = other->h();

	//Check for AABB Intersection
	if (_y + _h < other_y)
		return false;
	if (other_y + other_h < _y)
		return false;
	if (_x > other_x + other_w)
		return false;
	if (other_x > _x + _w)
		return false;

	return true;
}

void Collision_Mesh::print() {
	for (int y = 0; y < _h_scaled; y++, std::cout << std::endl)
		for (int x = 0; x < _w_scaled; x++)
			std::cout << (this->at(y * curr_length() / _down_scale + (frame_counter() * _w_scaled) + x) ? "#" : " ");
}

inline int Collision_Mesh::x() { return _entity->x(); }
inline int Collision_Mesh::y() { return _entity->y(); }
inline int Collision_Mesh::v_x() { return _entity->v_x(); }
inline int Collision_Mesh::v_y() { return _entity->v_y(); }
inline int Collision_Mesh::w() { return _entity->w(); }
inline int Collision_Mesh::h() { return _entity->h(); }
inline int Collision_Mesh::frame_counter() { return _entity->frame_counter(); }
inline int Collision_Mesh::curr_length() { return _entity->curr_frames() * _entity->w(); }
inline Collision_Mesh::Mesh Collision_Mesh::curr_mesh() { return _mesh[_entity->state()]; }
inline bool Collision_Mesh::at(int index) { return _mesh[_entity->state()]._matrix[index]; }
