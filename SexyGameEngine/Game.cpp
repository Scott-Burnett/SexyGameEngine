#include "Game.h"

Window Game::_window = Window("Main", 1900, 1080);

Keyboard Game::_keyboard = Keyboard();
Mouse Game::_mouse = Mouse();

Level Game::_level = Level("Level1");

Game::Game() {
	// Initialize player
	_player = Player(120, 120, 120, 120);
	_player.linkComponents();

	// Start game loop
	this->Play();
}

Game::~Game() {
}

void Game::GetEvents() {
	SDL_PumpEvents();
	_mouse.GetMouseState();
}

void Game::Play() {

	const int frame_delay = 1000 / fps;
	Uint32 frame_start;
	int frame_time;

	while (!_window.isClosed()) {
		//Get frame start time
		frame_start = SDL_GetTicks();

		//Get input
		this->GetEvents();

		//Affect Objects
		_player.Update();

		//Update Window
		_player.draw();
		_window.clear();

		//Get frame time
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time)
			SDL_Delay(frame_delay - frame_time);
	}
}