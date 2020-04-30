#pragma once
#include <vector>
#include"Coordinate.h"
#include "Status.h"

class Board
{
private:
	Coordinate size;
	int mines;
	int marked;
	std::vector<std::vector<Status>> statusMap;
	std::vector<std::vector<int>> map;  //-1 Mine, 0-8 numbers

public:
	Coordinate cursor_pos;

	Board();
	Board(Coordinate size, int mines);
	Coordinate getSize()const { return size; }
	Coordinate getCursor()const { return cursor_pos; }
	std::vector<std::vector<int>> getMap() const { return map; }
	std::vector<std::vector<Status>> getStatus() const { return statusMap; }
	int getMines() const { return mines; }
	int getMarked() const { return marked; }
	void setMarked(int x) { this->marked = x; }
	void setStatus(int x, int y, Status status) { this->statusMap[x][y] = status; }
	void draw();
	bool openCell(int x, int y);
	int checkBoard();
	void randomMines();
	void createMap();
};
