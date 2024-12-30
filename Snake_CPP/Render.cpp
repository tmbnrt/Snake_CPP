#include "Render.h"
#include "Logic.h"
#include <SDL.h>
#include <iostream>

Render::Render(int grid_row, int grid_col, int cell_size_px)
	: grid_row(grid_row), grid_col(grid_col), cell_size_px(cell_size_px) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("SDL cannot be initialized!");
		std::cerr << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow("Snake Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		grid_col * cell_size_px,
		grid_row * cell_size_px,
		SDL_WINDOW_SHOWN);

	if (!window) {
		SDL_Quit();
		throw std::runtime_error("Cannot create window!");
		std::cerr << "Window cannot be created! Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!render) {
		throw std::runtime_error("Renderer cannot be created!");
		std::cerr << "Renderer cannot be created! Error: " << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}
}

Render::~Render() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

static bool partOfSnake(Snake snake, int i, int j) {
	bool snake_part = false;
	for (int k = 0; k < snake.pos_col.size(); k++)
		if (i == snake.pos_col[k] && j == snake.pos_row[k])
			return true;

	return false;
}

void Render::rend(Snake snake) {
	// Background
	SDL_SetRenderDrawColor(render, 200, 200, 200, 255);

	// Clear back buffer
	SDL_RenderClear(render);

	// Field
	for (int i = 0; i < snake.field.size(); i++) {		// height
		for (int j = 0; j < snake.field[0].size(); j++) {		// width
			SDL_Rect rect = { j * cell_size_px, i * cell_size_px, cell_size_px, cell_size_px };

			if (j == snake.food_pos[0] && i == snake.food_pos[1])
				SDL_SetRenderDrawColor(render, 255, 0, 0, 255);	// red
			else if (partOfSnake(snake, j, i))
				SDL_SetRenderDrawColor(render, 0, 0, 0, 255);	// green
			else
				SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
			
			SDL_RenderFillRect(render, &rect);

			// Frame
			SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
			SDL_RenderDrawRect(render, &rect);
		}		
	}

	// Switch to front buffer
	SDL_RenderPresent(render);
}