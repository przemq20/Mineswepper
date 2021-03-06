#define MINE -1
#include "game.h"
#include "Board.h"
#include "Coordinate.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include "Status.h"
#include <MMsystem.h>

Board::Board() : marked(0), size(0, 0), cursor_pos(0, 0), mines(0) {}

Board::Board(Coordinate size, int mines) : marked(0), mines(mines), cursor_pos(size.getx() / 2 + 1, size.gety() / 2 + 1), size(size) {
	map.resize(size.gety());
	statusMap.resize(size.gety());
	for (int i = 0; i < size.gety(); i++) {
		statusMap[i].resize(size.getx(), CLOSED);
		map[i].resize(size.getx(), 0);
	}

	this->randomMines();
	this->createMap();
}

void Board::randomMines() {
	int indexX, indexY;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < mines; i++) {
		indexX = rand() % (size.getx());
		indexY = rand() % (size.gety());
		if (this->map[indexX][indexY] == MINE || ((indexX <= size.getx() / 2 + 1 && indexX >= size.getx() / 2 - 1) && (indexY <= size.getx() / 2 + 1 && indexY >= size.getx() / 2 - 1))) {
			i--;
			continue;
		}
		else {
			this->map[indexX][indexY] = MINE;
		}
	}
}

void Board::createMap() {
	for (int i = 0; i < size.gety(); i++) {
		for (int j = 0; j < size.getx(); j++) {
			if (map[i][j] != MINE) {
				if (i - 1 >= 0 && j - 1 >= 0 && map[i - 1][j - 1] == MINE) {
					map[i][j]++;
				}
				if (i - 1 >= 0 && map[i - 1][j] == MINE) {
					map[i][j]++;
				}
				if (j - 1 >= 0 && map[i][j - 1] == MINE) {
					map[i][j]++;
				}
				if (i + 1 < size.gety() && j - 1 >= 0 && map[i + 1][j - 1] == MINE) {
					map[i][j]++;
				}
				if (i - 1 >= 0 && j + 1 < size.getx() && map[i - 1][j + 1] == MINE) {
					map[i][j]++;
				}
				if (i + 1 < size.gety() && map[i + 1][j] == MINE) {
					map[i][j]++;
				}
				if (j + 1 < size.getx() && map[i][j + 1] == MINE) {
					map[i][j]++;
				}
				if (i + 1 < size.gety() && j + 1 < size.getx() && map[i + 1][j + 1] == MINE) {
					map[i][j]++;
				}
			}
		}
	}
}

void Board::draw() {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	int index = 0;
	Coordinate coordinate = this->getSize();
	int x = coordinate.getx();
	int y = coordinate.gety();
	int placeNumber;
	int status;

	for (int row = 0; row < y + 2; row++) {
		for (int col = 0; col < (x * 2) + 3; col++) {
			if (row == 0) {
				if (col == 0) {
					std::cout << "+";
				}
				else if (col == ((x * 2) + 2)) {
					std::cout << "+\n";
				}
				else {
					std::cout << "-";
				}
			}
			else if (row == (y + 1)) {
				if (col == 0) {
					std::cout << "+";
				}
				else if (col == ((x * 2) + 2)) {
					std::cout << "+\n";
				}
				else {
					std::cout << "-";
				}
			}
			else {
				if (col == 0) {
					std::cout << "|";
				}
				else if (col == ((x * 2) + 2)) {
					std::cout << "|\n";
				}
				else if (row == cursor_pos.gety() && col == ((cursor_pos.getx() - 1) * 2) + 1) {
					std::cout << "[";
				}
				else if (row == cursor_pos.gety() && col == ((cursor_pos.getx() - 1) * 2) + 3) {
					std::cout << "]";
				}
				else if (col % 2 == 1) {
					std::cout << " ";
				}
				else {
					placeNumber = getMap()[index / y][index % y];
					status = getStatus()[index / y][index % y];
					switch (status) {
					case 0: // Closed
						std::cout << "-";
						break;

					case 1: // Markded
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 116);
						std::cout << "X";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						break;

					case 2: // Opened
						if (placeNumber == 0) {
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
							std::cout << " ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

						}
						else {
							// Color the text.
							if (placeNumber == 1) {
								//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
								std::cout << placeNumber;
							}
							else if (placeNumber == 2) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 175);
								std::cout << placeNumber;
							}
							else if (placeNumber == 3) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
								std::cout << placeNumber;
							}
							else if (placeNumber == 4) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 96);
								std::cout << placeNumber;
							}
							else if (placeNumber == 5) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);
								std::cout << placeNumber;
							}
							else if (placeNumber == 6) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 176);
								std::cout << placeNumber;
							}
							else if (placeNumber == 7) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
								std::cout << placeNumber;
							}
							else if (placeNumber == 8) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 208);
								std::cout << placeNumber;
							}
							else if (placeNumber == MINE) {
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
								std::cout << "*";
							}
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						}
						break;

					default:
						break;
					}
					index++;
				}
			}
		}
	}
}

bool Board::openCell(int x, int y) {
	int status = statusMap[y - 1][x - 1];

	if (status != OPENED && status != MARKED) {
		setStatus(y - 1, x - 1, OPENED);

		if (map[y - 1][x - 1] == 0) {
			if ((x - 1 >= 1 && y - 1 >= 1)) {
				openCell(x - 1, y - 1);
			}
			if ((x - 1 >= 1 && x + 1 <= size.getx())) {
				openCell(x - 1, y);
			}
			if ((x - 1 >= 1 && y + 1 <= size.gety())) {
				openCell(x - 1, y + 1);
			}
			if ((y - 1 >= 1)) {
				openCell(x, y - 1);
			}
			if ((y + 1 <= size.gety())) {
				openCell(x, y + 1);
			}
			if ((x + 1 <= size.getx()) && y - 1 >= 1) {
				openCell(x + 1, y - 1);
			}
			if ((x + 1 <= size.getx())) {
				openCell(x + 1, y);
			}
			if ((x + 1 <= size.getx()) && y + 1 <= size.gety()) {
				openCell(x + 1, y + 1);
			}
			return true;
		}
	}
	return false;
}


int Board::checkBoard() {
	int i, j;
	bool unopend_cell_exist = false;

	for (i = 0; i < size.gety(); i++) {
		for (j = 0; j < size.getx(); j++) {
			if (map[i][j] == MINE && statusMap[i][j] == OPENED) {
				return 1;
			}
			if (map[i][j] != MINE && statusMap[i][j] == CLOSED) unopend_cell_exist = true;
		}
	}

	if (unopend_cell_exist) {
		return 0;
	}
	else {
		return 2;
	}
}
