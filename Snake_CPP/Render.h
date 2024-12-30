#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include "Logic.h"


class Render
{
public:
	Render(int grid_rows, int grid_columns, int cell_size_px);
	~Render();
	void								rend(Snake snake);

private:
	SDL_Window*							window;
	SDL_Renderer*						render;
	int									grid_row;
	int									grid_col;
	int									cell_size_px;
};

#endif