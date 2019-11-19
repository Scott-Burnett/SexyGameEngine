#include "Level.h"

// Stuct TileMap
Level::TileMap::TileMap(){
}

Level::TileMap::TileMap(const std::string &dir) {
	SDL_PixelFormat *pixel_format;
	int bpp, length;
	Uint8 *p;
	Uint32 pixel;
	Uint8 r, g, b, a;

	SDL_Surface *surface = IMG_Load((dir + "/Tiles/tiles.png").c_str);
	if (!surface) std::cerr << "Failed to create surface: " <<  std::endl;

	pixel_format = surface->format;
	bpp = pixel_format->BytesPerPixel;
	length = surface->w * surface->h * bpp;

	_w = surface->w;
	_h = surface->h;
	_tileCount = _w * _h;

	_matrix = new Tile[_tileCount];

	for (int i = 0, k = 0; k < length; k += bpp, i++) {
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

		// Construct Tile
		_matrix[i] = (a > 0) ?
			Tile(i % _w, i / _w, Empty) : Tile(i % _w, i / _w, Solid);

		_matrix[i].linkComponents();
	}

	SDL_FreeSurface(surface);
}

Tile* Level::TileMap::get(int x, int y) {
	x /= TILE_LENGTH;
	y /= TILE_LENGTH;
	return &_matrix[y * _w + x];
}

void Level::TileMap::draw(){
	for (int i = 0; i < _tileCount; i++)
		_matrix[i].draw();
}
// TileMap

Level::Level() {
}

Level::Level(const std::string &root_dir) {
	_x = 0;
	_y = 0;

	_root_dir = root_dir;

	// Construct Tiles
	_tiles = new TileMap(root_dir);

	_w = _tiles->_w * TILE_LENGTH;
	_h = _tiles->_h * TILE_LENGTH;
}

Level::~Level() {
}

bool Level::at(int x, int y) {

	
	return true;
}

void Level::collideEntities(Entity *a, Entity *b) {
	Collision_Mesh::Edge edge = a->intersectEdge(b);
	if (edge == Collision_Mesh::None)
		return;
	Vector2D location = b->intersect(a);
	if (location. x == -1 && location.y == -1)
		return;
	Vector2D displacement = a->displace(location, edge);
	b->_v_x += displacement.x;
	b->_v_y += displacement.y;
}

void Level::collideWith(Entity *other) {
	Tile *e;

	// Top Left
	e = _tiles->get(other->_x, other->_y);
	collideEntities(e, other);

	// Top Right
	e = _tiles->get(other->_x + other->_w, other->_y);
	collideEntities(e, other);

	// Bottom Left
	e = _tiles->get(other->_x, other->_y + other->_h);
	collideEntities(e, other);

	// Bottom Right
	e = _tiles->get(other->_x + other->_w, other->_y + other->_h);
	collideEntities(e, other);
}

void Level::draw() {
	// Draw tiles
	_tiles->draw();	
}

void Level::Update() {

}