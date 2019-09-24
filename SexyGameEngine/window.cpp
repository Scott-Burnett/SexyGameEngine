#include "window.h"
#include <SDL_image.h>
#include <iostream>

SDL_Renderer *Window::_renderer = nullptr;

Window::Window() {
}

Window::Window(const std::string &title, int width, int height) : 
_title(title), _width(width), _height(height) {
	_closed = !init();
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	IMG_Quit();
	SDL_Quit();
}

bool Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "Failed to initialize SDL_VIDEO\n";
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		std::cerr << "Failed to initialize IMG";
		return false;
	}

	_window = SDL_CreateWindow(
		_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width,
		_height,
		0//FLAGS
	);

	if (_window == nullptr) {
		std::cerr << "Failed to create window\n";
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (_renderer == nullptr) {
		std::cerr << "Failed to create renderer\n";
		return false;
	}
	std::cout << "SDL INITIALIZED" << std::endl;
	return true;
}

void Window::pollEvents(SDL_Event &event) {
	switch (event.type) {
	case SDL_QUIT:
		_closed = true;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			_closed = true;
			break;
		default:
			break;
		}
		break;
	}
}

void Window::clear() const {
	SDL_RenderPresent(_renderer);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
	SDL_RenderClear(_renderer);	
}