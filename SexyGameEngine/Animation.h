#pragma once
#include "window.h"

static class Animation {
public: 
	SDL_Texture *_texture;
	int _frames;
	int _w, _h;

	Animation();
	Animation(int w, int h, const std::string &path);
	~Animation();

	SDL_Texture* get();
};
