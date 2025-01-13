#pragma once
#include<vector>
#include<raylib.h>


class Grid {
public:
	Grid();
	void Initialise();
	void Print();
	int grid[20][10];
	void draw();
	bool isCellOutside(int row, int col);
	bool isCellEmpty(int row, int col);
	int clearFullRows();
private:
	bool isRowFull(int row);
	void clearRow(int row);
	void moveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;
};