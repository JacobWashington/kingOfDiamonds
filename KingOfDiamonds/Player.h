#pragma once
#include <iostream>
#include <string>

class Player {

public:
	std::string playerName;

	Player() {
		std::string name;

		std::cin >> name;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		setPlayerName(name);
	}

	std::string getPlayerName() {
		return this->playerName;
	}

private:
	void setPlayerName(std::string name) {
		this->playerName = name;
	}

};

