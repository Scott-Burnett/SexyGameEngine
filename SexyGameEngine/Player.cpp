#include "Player.h"
#include "Game.h"

Player::Player(int x, int y, int w, int h)
{
	_root_dir = PLAYER_ROOT_DIR;

	_x = x;
	_y = y;
	_w = w;
	_h = h;

	_v_x = 0;
	_v_y = 0;
	_direction = 0;

	_states = _player_states;

	_state = FALL_RIGHT;
	_num_states = PLAYER_NUM_STATES;
	_frame_counter = 0;
	_curr_frames = _states[_state].frames();

	_fps = PLAYER_FPS;

	_sprite = new Sprite(this, 30, 30, PLAYER_ANIMATIONS);
	_mesh = new Collision_Mesh(this, 4, PLAYER_MESH);

	_start_time = SDL_GetTicks();
}

Player::Player() {
}

Player::~Player() {
}

void Player::Update() {
	switch (_state) {
	case IDLE_RIGHT:
		if (Game::mouseState(BTN_ATTACK_LIGHT)) {
			// START LIGHT ATTACK
			break;
		}
		if (Game::mouseState(BTN_ATTACK_HEAVY)) {
			// START HEAVY ATTACK
			break;
		}
		if (Game::keyState(KEY_JUMP)) {
			newState(JUMP_RIGHT);
		}
		if (Game::keyState(KEY_DOWN)) { 
			
		}
		if (Game::keyState(KEY_RIGHT)) {
			_v_x += 10;
		}
		if (Game::keyState(KEY_LEFT)) {
			_v_x -= 10;
			newState(IDLE_LEFT);
		}
		proceedWithState();
		break;
	case IDLE_LEFT:
		if (Game::mouseState(BTN_ATTACK_LIGHT)) {
			// START LIGHT ATTACK
			break;
		}
		if (Game::mouseState(BTN_ATTACK_HEAVY)) {
			// START HEAVY ATTACK
			break;
		}
		if (Game::keyState(KEY_JUMP)) {
			newState(JUMP_LEFT);
		}
		if (Game::keyState(KEY_DOWN)) {

		}
		if (Game::keyState(KEY_RIGHT)) {
			_v_x += 10;
			newState(IDLE_RIGHT);
		}
		if (Game::keyState(KEY_LEFT)) {
			_v_x -= 10;
		}
		proceedWithState();
		break;
		break;
	case RUN_RIGHT:
		break;
	case RUN_LEFT:
		break;
	case JUMP_RIGHT:
		if (Game::keyState(KEY_JUMP)) {
			if (Game::mouseState(BTN_ATTACK_LIGHT)) {
				// START LIGHT ATTACK
				break;
			}
			if (Game::mouseState(BTN_ATTACK_HEAVY)) {
				// START HEAVY ATTACK
				break;
			}
			if (Game::keyState(KEY_DOWN)) {

			}
			if (Game::keyState(KEY_RIGHT)) {
				_v_x += 10;
			}
			if (Game::keyState(KEY_LEFT)) {
				_v_x -= 10;
				_state = (JUMP_LEFT);
			}
			switch (_frame_counter) {
			case 0:
				_v_y -= 30;
				proceedWithState();
				break;
			case 1:
				_v_y -= 20;
				proceedWithState();
				break;
			case 2:
				_v_y -= 15;
				proceedWithState();
				break;
			case 3:
				_v_y -= 5;
				proceedWithState();
				break;
			case 4:
			case 5:	
			case 6:
			case 7:
			case 8:
				_v_y = 0;
				newState(FALL_RIGHT);
				break;
			default:
				break;
			}	
		}
		else {
			newState(FALL_RIGHT);

			if (Game::mouseState(BTN_ATTACK_LIGHT)) {
				// START LIGHT ATTACK
				break;
			}
			if (Game::mouseState(BTN_ATTACK_HEAVY)) {
				// START HEAVY ATTACK
				break;
			}
			if (Game::keyState(KEY_DOWN)) {

			}
			if (Game::keyState(KEY_RIGHT)) {
				_v_x += 10;
			}
			if (Game::keyState(KEY_LEFT)) {
				_v_x -= 10;
				newState(FALL_LEFT);
			}

		}
		break;
	case JUMP_LEFT:
		if (Game::keyState(KEY_JUMP)) {
			if (Game::mouseState(BTN_ATTACK_LIGHT)) {
				// START LIGHT ATTACK
				break;
			}
			if (Game::mouseState(BTN_ATTACK_HEAVY)) {
				// START HEAVY ATTACK
				break;
			}
			if (Game::keyState(KEY_DOWN)) {

			}
			if (Game::keyState(KEY_RIGHT)) {
				_v_x += 10;
				_state = JUMP_RIGHT;
			}
			if (Game::keyState(KEY_LEFT)) {
				_v_x -= 10;

			}
			switch (_frame_counter) {
			case 0:
				_v_y -= 30;
				proceedWithState();
				break;
			case 1:
				_v_y -= 20;
				proceedWithState();
				break;
			case 2:
				_v_y -= 15;
				proceedWithState();
				break;
			case 3:
				_v_y -= 5;
				proceedWithState();
				break;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
				_v_y = 0;
				newState(FALL_LEFT);
				break;
			default:
				break;
			}
		}
		else {
			newState(FALL_LEFT);

			if (Game::mouseState(BTN_ATTACK_LIGHT)) {
				// START LIGHT ATTACK
				break;
			}
			if (Game::mouseState(BTN_ATTACK_HEAVY)) {
				// START HEAVY ATTACK
				break;
			}
			if (Game::keyState(KEY_DOWN)) {

			}
			if (Game::keyState(KEY_RIGHT)) {
				_v_x += 10;
				_state = FALL_RIGHT;
			}
			if (Game::keyState(KEY_LEFT)) {
				_v_x -= 10;
			}

		}
		break;
	case DASH_RIGHT:
		break;
	case DASH_DOWN_RIGHT:
		break;
	case DASH_DOWN:
		break;
	case DASH_DOWN_LEFT:
		break;
	case DASH_LEFT:
		break;
	case DASH_UP_LEFT:
		break;
	case DASH_UP:
		break;
	case DASH_UP_RIGHT:
		break;
	case SLIDE_RIGHT:
		break;
	case SLIDE_LEFT:
		break;
	case FALL_RIGHT:
		_v_y += GRAVITY;
		if (Game::mouseState(BTN_ATTACK_LIGHT)) {
			// START LIGHT ATTACK
			break;
		}
		if (Game::mouseState(BTN_ATTACK_HEAVY)) {
			// START HEAVY ATTACK
			break;
		}
		if (Game::keyState(KEY_DOWN)) {

		}
		if (Game::keyState(KEY_RIGHT)) {
			_v_x += 10;
		}
		if (Game::keyState(KEY_LEFT)) {
			_state = FALL_LEFT;
			_v_x -= 10;
		}

		if (_y >= 750)
			newState(IDLE_RIGHT);
		else
			proceedWithState();
		break;
	case FALL_LEFT:
		_v_y += GRAVITY;

		if (Game::mouseState(BTN_ATTACK_LIGHT)) {
			// START LIGHT ATTACK
			break;
		}
		if (Game::mouseState(BTN_ATTACK_HEAVY)) {
			// START HEAVY ATTACK
			break;
		}
		if (Game::keyState(KEY_DOWN)) {

		}
		if (Game::keyState(KEY_RIGHT)) {
			_v_x += 10;
			_state = FALL_RIGHT;
		}
		if (Game::keyState(KEY_LEFT)) {
			_v_x -= 10;
		}

		if (_y >= 750)
			newState(IDLE_LEFT);
		else
			
			proceedWithState();
		break;
	case ATTACK_LIGHT:
		break;
	case ATTACK_HEAVY:
		break;
	case USE_ITEM:
		break;
	case IN_MENUE:
		break;
	case RESTING:
		break;
	case DEAD:
		break;
	default:
		break;
	}	

	// Debug stuff
	std::cout <<"mX: " << Game::_mouse.x() << " mY: " << Game::_mouse.y() << std::endl;
	std::cout << "x: " << std::to_string(_x) << " y: " << std::to_string(_y) << std::endl;
	std::cout << "state: " << std::to_string(_state) << std::endl;
	std::cout << "fc: " << std::to_string(_frame_counter) << std::endl << std::endl;
}

void Player::draw() {
	_sprite->draw();
	// std::cout << "Player:" << std::endl;
	// _mesh->print();
}
