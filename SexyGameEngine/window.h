#pragma once

#include <string>
#include <SDL.h>

class Window {
public:
	Window();
	Window(const std::string &title, int width, int height);
	~Window();

	void pollEvents(SDL_Event &event);
	void clear() const;

	inline bool isClosed() const { return _closed; } 

	static SDL_Renderer *_renderer;

private:
	bool init();

	std::string _title;
	int _width = 1600;
	int _height = 900;
	bool _closed = false;
	SDL_Window *_window = nullptr; 	
};