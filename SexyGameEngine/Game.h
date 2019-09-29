#pragma once
#include "Window.h"
#include "Entity.h"
#include "Player.h"
#include "Level.h"
#include <iostream>
#include <SDL.h>

struct Keyboard {
private:
	const Uint8 * _keyboard_state;
public:
	Keyboard() : _keyboard_state(SDL_GetKeyboardState(NULL)) {}
	inline Uint8 keyState(const int key_code) { return _keyboard_state[key_code]; }
};

struct Mouse {
private:
	Uint32 _mouse_state;
	int _cursor_x, _cursor_y;
public:
	Mouse() : _mouse_state(SDL_GetMouseState(&_cursor_x, &_cursor_y)) {}
	inline Uint32 mouseState(const int button_code) { return _mouse_state & button_code; }
	inline int x() { return _cursor_x; }
	inline int y() { return _cursor_y; }
	void GetMouseState() { _mouse_state = SDL_GetMouseState(&_cursor_x, &_cursor_y); }
};

const int
// Keyboard keycode mapping
KEY_RIGHT = SDL_SCANCODE_D,
KEY_LEFT = SDL_SCANCODE_A,
KEY_UP = SDL_SCANCODE_W,
KEY_DOWN = SDL_SCANCODE_S,
KEY_JUMP = SDL_SCANCODE_SPACE,
KEY_DASH = SDL_SCANCODE_LSHIFT,
KEY_SLIDE = SDL_SCANCODE_LCTRL,
KEY_USE_ITEM = SDL_SCANCODE_Q,
KEY_MENUE = SDL_SCANCODE_TAB,
// Mouse button mask mapping
BTN_ATTACK_LIGHT = SDL_BUTTON_LEFT,
BTN_ATTACK_HEAVY = SDL_BUTTON_RIGHT;

class Game {
public:
	Game();
	~Game();

	static Window _window;

	static Keyboard _keyboard;
	static Mouse _mouse;

private:
	const int fps = 60;
	Level *_level;
	Player *_player;


public:
	void Play();
	void GetEvents();
	// Return Key State
	inline static Uint8 keyState(int key_code) { return _keyboard.keyState(key_code); }

	// Return Mouse Button State
	inline static Uint32 mouseState(int button_mask) { return _mouse.mouseState(button_mask); }
};