#pragma once

#include "json.hpp"
class leaderboard
{
private:
	//nlohmann::json j;

public:
	bool check_availability(char difficulty, int time);
	void new_entry(char diffiiculty, int time);
	void print_leaderboard();
};
