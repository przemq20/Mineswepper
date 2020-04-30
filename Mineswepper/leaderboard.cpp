#include "leaderboard.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <sys/stat.h>

struct result {
	std::string name;
	int score;
};

void gotoxy1(int x, int y)
{
	COORD Pos = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

bool sortResults(result a, result b) {
	if (a.score < b.score) return true;
	return false;
}

std::string parseCharToLevel(char difficulty) {
	std::string dif;
	switch (difficulty)
	{
	case '1':
		return "easy";
	case '2':
		return "medium";
	case '3':
		return "hard";
	default:
		throw("");
	}
}

bool leaderboard::check_availability(char difficulty, int time) {
	std::string dif = parseCharToLevel(difficulty);

	const std::string filename = "file.json";
	std::ifstream reader(filename);
	nlohmann::json j;
	reader >> j;
	reader.close();
	result res;
	std::vector<result> results;
	for (const auto& easy : j["leaderboard"][dif]) {
		res.name = easy["name"];
		res.score = easy["score"];
		results.push_back(res);
	}
	sort(results.begin(), results.end(), sortResults);

	if (results.size() < 10) {
		return true;
	}
	else if (results[9].score > time) {
		std::ofstream writer;
		writer.open(filename);
		results.pop_back();
		j["leaderboard"].erase(dif);
		for (int i = 0; i < (int)results.size(); i++) {
			nlohmann::json jj;
			jj["name"] = results[i].name;
			jj["score"] = results[i].score;
			j["leaderboard"][dif].push_back(jj);
		}
		writer << j.dump(4);
		return true;
	}
	else {
		return false;
	}
}

void leaderboard::new_entry(char diffiiculty, int time) {

	std::string dif = parseCharToLevel(diffiiculty);

	std::string name;
	system("cls");
	printf("Please enter your name (max 10 characters): ");
	do {
		if (name.size() > 10) {
			std::cout << "Too long name" << std::endl;
		}
		std::cin >> name;
		system("cls");
	} while (name.size() > 10);

	const std::string filename = "file.json";
	std::ifstream reader(filename);
	nlohmann::json j;
	reader >> j;
	reader.close();
	std::vector<result>results;
	result res;
	for (const auto& easy : j["leaderboard"][dif]) {
		res.name = easy["name"];
		res.score = easy["score"];
		results.push_back(res);
	}
	res.name = name;
	res.score = time;
	results.push_back(res);
	sort(results.begin(), results.end(), sortResults);

	std::ofstream writer;
	writer.open(filename);
	j["leaderboard"].erase(dif);
	for (int i = 0; i < (int)results.size(); i++) {
		nlohmann::json jj;
		jj["name"] = results[i].name;
		jj["score"] = results[i].score;
		j["leaderboard"][dif].push_back(jj);
	}
	writer << j.dump(4);
}

void leaderboard::print_leaderboard() {
	system("cls");
	const std::string filename = "file.json";
	std::ifstream reader(filename);
	std::vector<result> resultsEasy;
	std::vector<result> resultsMedium;
	std::vector<result> resultsHard;

	nlohmann::json j;
	reader >> j;
	reader.close();

	result res;
	for (const auto& easy : j["leaderboard"]["easy"]) {
		res.name = easy["name"];
		res.score = easy["score"];
		resultsEasy.push_back(res);
	}
	for (const auto& easy : j["leaderboard"]["medium"]) {
		res.name = easy["name"];
		res.score = easy["score"];
		resultsMedium.push_back(res);
	}
	for (const auto& easy : j["leaderboard"]["hard"]) {
		res.name = easy["name"];
		res.score = easy["score"];
		resultsHard.push_back(res);
	}
	sort(resultsEasy.begin(), resultsEasy.end(), sortResults);
	gotoxy1(6, 0);
	std::cout << "EASY";
	gotoxy1(21, 0);
	std::cout << "MEDIUM";
	gotoxy1(38, 0);
	std::cout << "HARD";
	for (int i = 0; i < (int)resultsEasy.size(); i++) {
		gotoxy1(0, i + 1);
		std::cout << resultsEasy[i].name;
		gotoxy1(11, i + 1);
		std::cout << resultsEasy[i].score << std::endl;
	}
	sort(resultsMedium.begin(), resultsMedium.end(), sortResults);
	for (int i = 0; i < (int)resultsMedium.size(); i++) {
		gotoxy1(16, i + 1);
		std::cout << resultsMedium[i].name;
		gotoxy1(27, i + 1);
		std::cout << resultsMedium[i].score << std::endl;
	}
	sort(resultsHard.begin(), resultsHard.end(), sortResults);
	for (int i = 0; i < (int)resultsHard.size(); i++) {
		gotoxy1(32, i + 1);
		std::cout << resultsHard[i].name;
		gotoxy1(43, i + 1);
		std::cout << resultsHard[i].score << std::endl;
	}
	_getch();
}
