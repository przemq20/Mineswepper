#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <iostream>
#include "game.h"
#include "Coordinate.h"
#include "Board.h"
#include <time.h>
#include <windows.h>
#include "menu.h"
#include "leaderboard.h"

Menu men;
leaderboard leaderBoard;

int main() {
	PlaySound(TEXT("smb_powerup.wav"), NULL, SND_FILENAME | SND_ASYNC);
	char input = 0;
	char input1 = 0;
	char input2 = 0;
	int result_time;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	while (input != 'q' && input != 'Q') {
		result_time = -1;
		int result = 0;
		input = men.mainMenu();
		input1 = '0';
		input2 = '0';
		switch (input) {
		case '1':

			while (input1 != 'q' && input1 != 'Q') {
				input1 = men.gameMenu();
				if (input1 == '1') {
					game newGame(11, 11, 10);
					result_time = newGame.startGame();
					result = newGame.getStatus();
				}
				else if (input1 == '2') {
					game newGame(19, 19, 40);
					result_time = newGame.startGame();
					result = newGame.getStatus();
				}
				else if (input1 == '3') {
					game newGame(23, 23, 99);
					result_time = newGame.startGame();
					result = newGame.getStatus();
				}

				if (result == 2) {

					if (leaderBoard.check_availability(input1, result_time)) {

						leaderBoard.new_entry(input1, result_time);
					}
					leaderBoard.print_leaderboard();
					result = 0;
				}
			}
		case '2':
			leaderBoard.print_leaderboard();
			break;
		default:
			break;
		}
	}
}
