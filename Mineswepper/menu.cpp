#include "menu.h"
#include<iostream>
#include <windows.h>
#include <conio.h>

char Menu::mainMenu() {
	// Clear screen.
	system("cls");
	dispBanner();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	std::cout << "\n===== Select menu =====\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "1. Play\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << "2. Leaderboard\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "Q. Quit\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	return _getch();
}

char Menu::gameMenu() {
	// Clear screen.
	system("cls");

	dispBanner();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

	std::cout << "\n===== Select difficulty =====\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	std::cout << "1. Play easy ()\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "2. Play medium ()\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::cout << "3. Play hard ()\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);

	std::cout << "Q. Quit\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	return _getch();
}

void Menu::dispBanner()
{ //will be moved to separate header later
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::cout << R"(
    ##     ##  ##  ##    ## ########  ######  ##      ## ######## ######## ########  ######## ########
    ###   ###  ##  ###   ## ##       ##    ## ##  ##  ## ##       ##       ##     ## ##       ##     ##
    #### ####  ##  ####  ## ##       ##       ##  ##  ## ##       ##       ##     ## ##       ##     ##
    ## ### ##  ##  ## ## ## ######    ######  ##  ##  ## ######   ######   ########  ######   ########
    ##     ##  ##  ##  #### ##             ## ##  ##  ## ##       ##       ##        ##       ##   ##
    ##     ##  ##  ##   ### ##       ##    ## ##  ##  ## ##       ##       ##        ##       ##    ##
    ##     ##  ##  ##    ## ########  ######   ###  ###  ######## ######## ##        ######## ##     ##)";
	std::cout << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
