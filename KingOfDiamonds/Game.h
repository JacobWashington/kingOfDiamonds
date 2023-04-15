#pragma once
#include <iostream>
#include "Player.h"
#include "Round.h"

class Game
{
public:

	Game() {
		this->setNumPlayers();
		this->setPlayersPtr();
		this->startGame();
	}

	int getNumPlayers() {
		return this->numPlayers;
	}

	int getActivePlayers() {
		return this->activePlayers;
	}

	int getCurrRound() {
		return this->currRound;
	}

	double getAverageGuess() {
		return this->averageGuess;
	}

	Player* getPlayersPtr() {
		return this->playersPtr;
	}

private:
	int numPlayers;
	int activePlayers;
	int currRound = 0;
	double averageGuess;
	Player* playersPtr = nullptr;
	Player* finalWinner = nullptr;
	Player* roundWinner = nullptr;


	void setNumPlayers() {
		int numPlayers;

		std::cout << "\nEnter the number of players: ";
		std::cin >> numPlayers;
		std::cin.clear();
		std::cin.ignore(1000, '\n');

		this->numPlayers = numPlayers;
	}

	void setActivePlayers() {
		int activePlayers = 0;

		for (int i = 0; i < this->numPlayers; i++) {
			bool playerLifeStatus = (this->playersPtr + i)->getLifeStatus();
			if (playerLifeStatus) {
				activePlayers++;
			}
		}

		this->activePlayers = activePlayers;
	}

	void setPlayersPtr() {
		this->playersPtr = new Player[this->numPlayers];
	}

	void setFinalWinner(Player* ptr) {
		this->finalWinner = ptr;
	}

	void startGame() {
		system("cls");
		int roundNum = 1;
		do {
			Round currRound = Round(roundNum++, this->getNumPlayers(), this->getPlayersPtr(), this->finalWinner );
		
		} while (!this->finalWinner);

		endGame();
	}

	void endGame() {
		delete[] this->playersPtr;
		this->playersPtr = nullptr;
	}

};

