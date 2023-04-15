#pragma once
#include <iostream>
#include <string>

class Player
{

public:
	void newPlayer() {
		std::string name;

		std::cout << "\nEnter a name: ";
		std::cin >> name;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		setPlayerName(name);
	}

	std::string getPlayerName() {
		return this->playerName;
	}

	int getScore() {
		return this->score;
	}

	bool getLifeStatus() {
		return this->alive;
	}

	int getGuess() {
		return this->guess;
	}

	double getDistFromAverage() {
		return this->guessDistFromAverage;
	}

	void setScore(int pointAdjustment) {
		this->score += pointAdjustment;
	}

	void setLifeStatus() {
		this->alive = false;
	}

	void setGuess(int guess) {
		this->guess = guess;
	}

	void setGuessDistFromAverage(double average) {
		double guessDbl = double(this->guess);

		if (guessDbl < average) {
			this->guessDistFromAverage = average - guessDbl;
		}
		else {
			this->guessDistFromAverage = guessDbl - average;
		}
	}

	void setPlayerName(std::string name) {
		this->playerName = name;
	}

private:

	std::string playerName;
	int score = 0;
	bool alive = true;
	int guess;
	double guessDistFromAverage;

};

