#ifndef LOGIC_H
#define LOGIC_H

#include <vector>

struct Snake {
	std::vector<int> pos_row;
	std::vector<int> pos_col;
	std::vector<std::vector<int>> field;
	std::vector<int> food_pos;
};

class Logic
{
public:
	Logic(int size_h, int size_w, int init_length);
	//~Logic();
	
	int					start();

private:
	int					size_h;
	int					size_w;
	int					init_length;
	Snake				snake;
	void				move(char move_dir);
	int					borderCheck(char orientation, int value);
};

#endif