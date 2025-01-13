#pragma once
#include<vector>
#include<map>
#include "position.h"
#include "colors.h"

class Block {
public:
	Block();
	int id;
	std::map<int, std::vector<Position>> cells;
	void draw(int xoffset, int yoffset);
	void move(int rows, int cols);
	std::vector<Position> getCellPositions();
	void rotate();
	void undoRotation();
private:
	int cellSize;
	int state;
	std::vector<Color> colors;
	int rowOffset;
	int colOffset;
};