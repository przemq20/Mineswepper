#pragma once
#include "Board.h"
#include "Board.h"
#include "Coordinate.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>

class game
{
private:
	Board board;
	int status; // 0: continue game, 1: lost, 2: win, 3: quit order from user, 4: restart order from user
	unsigned int start_time;
	unsigned int end_time;

public:
	Board getBoard() const { return board; }

	game(int x, int y, int mines);
	int startGame();
	void draw();
	int getStatus() const { return status; }
};
