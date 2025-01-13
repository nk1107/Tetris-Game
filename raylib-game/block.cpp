#include "block.h"

Block::Block() {
	cellSize = 30;
	state = 0;
	rowOffset = 0;
	colOffset = 0;
	colors = getCellColors();
}

void Block::draw(int xoffset,int yoffset) {
	std::vector<Position> tiles = getCellPositions();
	for (Position item : tiles) {
		DrawRectangle(item.col * cellSize + xoffset, item.row * cellSize +yoffset, cellSize - 1, cellSize - 1, colors[id]);
	}
}

void Block::move(int rows, int cols) {
	rowOffset += rows;
	colOffset += cols;
}

std::vector<Position> Block::getCellPositions() {
	std::vector<Position> tiles = cells[state];
	std::vector<Position> movedTiles;
	bool check = 1;
	for (Position pos : tiles) {
		int newrow = pos.row + rowOffset;
		int newcol = pos.col + colOffset;
		
		Position newPos = Position(newrow, newcol);
		movedTiles.push_back(newPos);
	}
	return movedTiles;
}

void Block::rotate() {
	state += 1;
	state %= 4;
}

void Block::undoRotation() {
	state -= 1;
	if (state < 0) {
		state = cells.size() - 1;
	}
}