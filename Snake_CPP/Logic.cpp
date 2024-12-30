#include "Logic.h"
#include "Render.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

Logic::Logic(int size_h, int size_w, int init_length) : size_h(size_h), size_w(size_w), init_length(init_length) {
	std::vector<std::vector<int>> init_field(size_h, std::vector<int>(size_w));
	std::vector<int> pos_row;
	std::vector<int> pos_col;
	for (int i = 0; i < init_length; i++) {
		pos_row.push_back(1);
		pos_col.push_back(i + 1);
	}

	this->snake.pos_row = pos_row;
	this->snake.pos_col = pos_col;
	this->snake.field = init_field;
}

static bool cannibal(Snake snake) {
	for (int i = 0; i < snake.pos_col.size(); i++) {
		for (int j = 0; j < snake.pos_col.size(); j++) {
			if (i != j)
				if (snake.pos_row[i] == snake.pos_row[j] && snake.pos_col[i] == snake.pos_col[j])
					return true;
		}
	}

	return false;
}

static std::vector<int> randomFood(Snake snake) {
	std::vector<int> food{ 0, 0 };

	bool end = false;
	while (!end) {
		srand(time(0));
		int rand_h = rand() % snake.field.size();
		int rand_w = rand() % snake.field[0].size();

		for (int i = 0; i < snake.pos_row.size(); i++) {
			if (snake.pos_row[i] != rand_h && snake.pos_col[i] != rand_w) {
				food[0] = rand_h;
				food[1] = rand_w;
				end = true;
				return food;
			}				
		}
	}

	return food;
}

int Logic::borderCheck(char orientation, int value) {
	int border_h = snake.field.size();
	int border_w = snake.field[0].size();
	if (orientation == 'w') {
		if (value < 0)
			return border_w;
		if (value == border_w)
			return 0;
	}
	if (orientation == 'h') {
		if (value < 0)
			return border_h;
		if (value == border_h)
			return 0;
	}

	return value;
}

void Logic::move(char move_dir) {
	std::vector<int> pre_pos_row = snake.pos_row;
	std::vector<int> pre_pos_col = snake.pos_col;
	snake.pos_row.clear();
	snake.pos_col.clear();

	if (move_dir == 'r') {
		snake.pos_row.push_back(pre_pos_row[0]);
		snake.pos_col.push_back(borderCheck('w', pre_pos_col[0] + 1));
	}
	if (move_dir == 'l') {
		snake.pos_row.push_back(pre_pos_row[0]);
		snake.pos_col.push_back(borderCheck('w', pre_pos_col[0] - 1));
	}
	if (move_dir == 'u') {
		snake.pos_row.push_back(borderCheck('h', pre_pos_row[0] - 1));
		snake.pos_col.push_back(pre_pos_col[0]);
	}
	if (move_dir == 'd') {
		snake.pos_row.push_back(borderCheck('h', pre_pos_row[0] + 1));
		snake.pos_col.push_back(pre_pos_col[0]);
	}

	// Eat or not
	if (snake.pos_row[0] == snake.food_pos[1] && snake.pos_col[0] == snake.food_pos[0]) {
		for (int i = 0; i < pre_pos_row.size(); i++) {
			snake.pos_row.push_back(pre_pos_row[i]);
			snake.pos_col.push_back(pre_pos_col[i]);
		}
		snake.food_pos = randomFood(snake);
	}
	else {
		for (int i = 0; i < pre_pos_row.size() - 1; i++) {
			snake.pos_row.push_back(pre_pos_row[i]);
			snake.pos_col.push_back(pre_pos_col[i]);
		}
	}
}

int Logic::start() {
	char move_dir = 'l';			//  r: right   l: left   u: up   d: down
	int speed = 1;
	int cell_size_px = 10;

	Render rend(size_h, size_w, cell_size_px);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

	Uint32 startTime = SDL_GetTicks();

	snake.food_pos = randomFood(snake);

	bool feeding = true;
	while (feeding) {
		SDL_Event e;		

		if (SDL_GetTicks() - startTime >= 1000) {
			feeding = true;
		}		

		rend.rend(snake);

		if (cannibal(snake))
			return 1;

		// Check for Keyboard input
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_UP:
					if (move_dir != 'd')
						move_dir = 'u';
					break;
				case SDLK_DOWN:
					if (move_dir != 'u')
						move_dir = 'd';
					break;
				case SDLK_LEFT:
					if (move_dir != 'r')
						move_dir = 'l';
					break;
				case SDLK_RIGHT:
					if (move_dir != 'l')
						move_dir = 'r';
					break;
				default:
					break;
				}
			}
		}

		move(move_dir);
	}

	return 0;
}

