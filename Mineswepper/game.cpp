#define MINE -1
#include "game.h"


game::game(int x, int y, int mines) : status(0) {
	Coordinate coordinate(x, y);
	this->board = Board(coordinate, mines);
	this->start_time = (unsigned int)time(NULL);
}

void gotoxy(int x, int y)
{
	COORD Pos = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int game::startGame() {
	system("cls");
	int result_time = 0;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

	draw();
	Coordinate cursor_pos;
	while (true) {
		if (status != 0) break;

		char input = _getch();

		switch (input)
		{
		case 'w':
		case 'W':
			PlaySound(TEXT("Sound.wav"), NULL, SND_ASYNC);
			if (board.cursor_pos.gety() == 1) {
				board.cursor_pos.setY(board.getSize().gety());
			}
			else {
				board.cursor_pos.setY(board.cursor_pos.gety() - 1);
			}
			break;
		case 's':
		case 'S':
			PlaySound(TEXT("Sound.wav"), NULL, SND_ASYNC);
			if (board.cursor_pos.gety() == board.getSize().gety()) {
				board.cursor_pos.setY(1);
				break;
			}
			board.cursor_pos.setY(board.cursor_pos.gety() + 1);
			break;
		case 'a':
		case 'A':
			PlaySound(TEXT("Sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (board.cursor_pos.getx() == 1) {
				board.cursor_pos.setX(board.getSize().getx());
			}
			else {
				board.cursor_pos.setX(board.cursor_pos.getx() - 1);
			}
			break;
		case 'd':
		case 'D':
			PlaySound(TEXT("Sound.wav"), NULL, SND_ASYNC);
			if (board.cursor_pos.getx() == board.getSize().getx()) {
				board.cursor_pos.setX(1);
			}
			else {
				board.cursor_pos.setX(board.cursor_pos.getx() + 1);
			}
			break;
		case 'k':
		case 'K':
			if (board.getStatus()[board.cursor_pos.gety() - 1][board.cursor_pos.getx() - 1] == 0 && board.getMines() - board.getMarked() > 0) {
				board.setMarked(board.getMarked() + 1);
				board.setStatus(board.cursor_pos.gety() - 1, board.cursor_pos.getx() - 1, MARKED);
				PlaySound(TEXT("flag.wav"), NULL, SND_ASYNC);
			}
			else if (board.getStatus()[board.cursor_pos.gety() - 1][board.cursor_pos.getx() - 1] == 1) {
				board.setStatus(board.cursor_pos.gety() - 1, board.cursor_pos.getx() - 1, CLOSED);
				board.setMarked(board.getMarked() - 1);
				PlaySound(TEXT("flag.wav"), NULL, SND_ASYNC);
			}
			break;
		case 'o':
		case 'O':
			board.openCell(board.cursor_pos.getx(), board.cursor_pos.gety());
			PlaySound(TEXT("open.wav"), NULL, SND_ASYNC);
			status = board.checkBoard();
			break;
		case 'q':
		case 'Q':
			status = 3;
		}
		draw();
	}
	end_time = (unsigned int)time(NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);

	gotoxy(board.getSize().getx() * 2 + 5, 4);
	if (status == 2) {
		PlaySound(TEXT("Victory.wav"), NULL, SND_ASYNC);

		std::cout << "You won the game!";
		result_time = end_time - start_time;
	}
	else if (status == 1) {
		PlaySound(TEXT("Bomb+1.wav"), NULL, SND_ASYNC);

		std::cout << "You lost the game...";

		result_time = -1;
	}
	gotoxy(board.getSize().getx() * 2 + 5, 5);
	std::cout << "Press Q to exit.";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	char input2 = '0';
	while (1) {
		char input2 = _getch();
		if (input2 == 'q' || input2 == 'Q') {
			return  result_time;
		}
	}
}

void game::draw() {
	this->board.draw();
	unsigned int time_spent = (unsigned int)time(NULL) - start_time;
	gotoxy(2 * board.getSize().getx() + 5, 0);
	printf("====== GAME INFO ======");
	gotoxy(2 * board.getSize().getx() + 5, 1);
	printf("Position: %d, %d           ", board.cursor_pos.getx(), board.cursor_pos.gety());
	gotoxy(2 * board.getSize().getx() + 5, 2);
	printf("Mines: %d     ", board.getMines() - board.getMarked());
	gotoxy(2 * board.getSize().getx() + 5, 3);
	printf("Time: %02d:%02d    ", time_spent / 60, time_spent - (time_spent / 60 * 60));
	gotoxy(0, board.getSize().getx() + 1);
	printf("\n\nUse W, A, S, D for moving.\n");
	printf("O to open, K to mark.\n");
	printf("Q to quit.\n");
}
