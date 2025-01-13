#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid() {
	numRows = 20;
	numCols = 10;
	cellSize = 30;
	Initialise();
	colors = getCellColors();
}

void Grid::Initialise() {
	for (int row = 0;row < numRows;row++) {
		for (int col = 0;col < numCols;col++) {
			grid[row][col] = 0;
		}
	}
}

void Grid::Print() {
	for (int row = 0;row < numRows;row++) {
		for (int col = 0;col < numCols;col++) {
			std::cout << grid[row][col] << " ";
		}
		std::cout << "\n";
	}
}

void Grid::draw() {
	for (int i = 0;i < numRows;i++) {
		for (int j = 0;j < numCols;j++) {
			int cellval = grid[i][j];
			DrawRectangle(j * cellSize + 11, i * cellSize + 11, cellSize-1, cellSize-1, colors[cellval]);
		}
	}
}

bool Grid::isCellOutside(int row, int col) {
	if (row < 0 || row >= numRows || col < 0 || col >= numCols) {
		return true;
	}
	return false;
}

bool Grid::isCellEmpty(int row, int col){
	if (grid[row][col] == 0) {
		return true;
	}
	return false;
}

int Grid::clearFullRows(){
	int completed = 0;
	for (int row = numRows - 1; row >= 0;row--) {
		if (isRowFull(row)) {
			completed++;
		}
		else if (completed) {
			moveRowDown(row, completed);
		}
	}
	return completed;
}

bool Grid::isRowFull(int row){
	for (int col = 0;col < numCols;col++) {
		if (grid[row][col] == 0) {
			return false;
		}
	}
	return true;
}

void Grid::clearRow(int row){
	for (int col = 0;col < numCols;col++) {
		grid[row][col] = 0;
	}
}

void Grid::moveRowDown(int row, int numRows){
	for (int col = 0;col < numCols;col++) {
		grid[row+numRows][col] = grid[row][col];
	}
	clearRow(row);
}
