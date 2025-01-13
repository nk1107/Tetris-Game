#include "game.h"
#include <random>

Game::Game() {
	grid = Grid();
	blocks = getAllBlocks();
	currBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	gameover = false;
	score = 0;
}

void Game::updateScore(int linesCleared,int moveDownPoints){
	switch (linesCleared) {
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}
	score += moveDownPoints;
}

void Game::Reset() {
	grid.Initialise();
	blocks = getAllBlocks();
	currBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	score = 0;
}

Block Game::getRandomBlock() {
	if (blocks.empty()) {
		blocks = getAllBlocks();
	}
	int randomInd = rand() % blocks.size();
	Block block = blocks[randomInd];
	blocks.erase(blocks.begin() + randomInd);
	return block;
}

std::vector<Block> Game::getAllBlocks() {
	return { IBlock(),JBlock(),SBlock(),ZBlock(),OBlock(),LBlock(),TBlock() };
}

void Game::draw() {
	grid.draw();
	currBlock.draw(11,11);

	switch (nextBlock.id) {
	case 3: {
		nextBlock.draw(255, 290);
		break;
	}
	case 4:
		nextBlock.draw(255, 280);
		break;
	default:
		nextBlock.draw(270, 270);
		break;
	}
	
}

bool Game::isBlockOutside()
{
	std::vector<Position> tiles = currBlock.getCellPositions();

	for (Position pos : tiles) {
		if (grid.isCellOutside(pos.row, pos.col)) {
			return true;
		}
	}
	return false;
}

void Game::lockBlock(){
	std::vector<Position> tiles = currBlock.getCellPositions();
	for (Position pos : tiles) {
		grid.grid[pos.row][pos.col] = currBlock.id;
	}
	currBlock = nextBlock;
	if (!blockFits()) {
		gameover = true;
	}
	
	int rowsCleared = grid.clearFullRows();
	updateScore(rowsCleared, 0);
	nextBlock = getRandomBlock();
	
}

bool Game::blockFits(){
	std::vector<Position> tiles = currBlock.getCellPositions();
	for (Position item : tiles) {
		if (grid.isCellEmpty(item.row, item.col) == false) {
			return false;
		}
	}
	return true;
}


void Game::handleInput() {
	int keypressed = GetKeyPressed();

	if (gameover && keypressed) {
		gameover = false;
		Reset();
	}
	switch (keypressed) {
	case KEY_LEFT:
		moveBlockLeft();
		break;
	case KEY_RIGHT:
		moveBlockRight();
		break;
	case KEY_DOWN:
		moveBlockDown();
		updateScore(0, 1);
		break;
	case KEY_SPACE:
		rotateBlock();
		break;
	}
}

void Game::moveBlockLeft() {
	if (!gameover) {
		currBlock.move(0, -1);
		if (isBlockOutside() || !blockFits()) {
			currBlock.move(0, 1);
		}
	}
	

}
void Game::moveBlockRight() {
	if (!gameover) {
		currBlock.move(0, 1);
		if (isBlockOutside() || !blockFits()) {
			currBlock.move(0, -1);
		}
	}
	
}
void Game::moveBlockDown() {
	if (!gameover) {
		currBlock.move(1, 0);
		if (isBlockOutside() || !blockFits()) {
			currBlock.move(-1, 0);
			lockBlock();
		}
	}
	
}

void Game::rotateBlock() {
	if (!gameover) {
		currBlock.rotate();
		if (isBlockOutside()) {
			currBlock.undoRotation();
		}
	}
	
}

