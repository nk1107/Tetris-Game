#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
public:
	Game();
	Block getRandomBlock();
	std::vector<Block> getAllBlocks();
	void handleInput();
	void moveBlockLeft();
	void moveBlockRight();
	void moveBlockDown();
	void rotateBlock();
	void draw();
	Grid grid;
	bool gameover;
	int score;
private:
	void updateScore(int linesCleared, int moveDownPoints);
	void Reset();
	bool isBlockOutside();
	void lockBlock();
	bool blockFits();
	std::vector<Block> blocks;
	Block currBlock;
	Block nextBlock;
};