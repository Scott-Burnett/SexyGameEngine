#include "Animation.h"
#include "Game.h"
#include <SDL_image.h>
#include <iostream>

Animation::Animation() {

}

Animation::Animation(int w, int h, const std::string &path) :
_w(w), _h(h)
{
	SDL_Surface *surface = IMG_Load(path.c_str());

	if (!surface) std::cerr << "Failed to create surface: " << path.c_str() << std::endl;

	_texture = SDL_CreateTextureFromSurface(Game::_window._renderer, surface);

	if (!_texture) std::cerr << "Failed to create texture: " << path.c_str() << std::endl;

	_frames = surface->w / _w;

	SDL_FreeSurface(surface);
}
Animation::~Animation() {
}

SDL_Texture* Animation::get() {
	return _texture;
}