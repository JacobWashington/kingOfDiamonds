#pragma once
#include <iostream>
#include "Player.h"

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

	void setCurrRound() {
		this->currRound++;
	}

	void setAverageGuess() {
		double averageGuess = 0.0;

		for (int i = 0; i < this->numPlayers; i++) {
			averageGuess += (this->playersPtr + i)->getGuess();
		}

		this->averageGuess = (averageGuess / this->numPlayers)*0.8;
	}

	void setPlayersPtr() {
		this->playersPtr = new Player[this->numPlayers];
	}

	void setFinalWinner(Player* ptr) {
		this->finalWinner = ptr;
	}

	void setRoundWinner() {
		Player* tempWinner = nullptr;
		for (int i = 0; i < this->numPlayers; i++) {
			if (tempWinner) {

				if (tempWinner->getDistFromAverage() > (this->playersPtr + i)->getDistFromAverage()) {

					tempWinner->setScore(-1);
					tempWinner = (this->playersPtr + i);

				}
				else {
					(this->playersPtr + i)->setScore(-1);
				}
			}
			else {
				tempWinner = (this->playersPtr + i);
			}
		}

		this->roundWinner = tempWinner;
	}

	void handleRound() {
		for (int i = 0; i < this->numPlayers; i++) {
			bool playerLifeStatus = (this->playersPtr + i)->getLifeStatus();

			if (playerLifeStatus) {
				std::string playerName = (this->playersPtr + i)->getPlayerName();
				int guess;

				std::cout << '\n' << playerName << ", enter a number from 0 to 100: ";
				std::cin >> guess;

				(this->playersPtr + i)->setGuess(guess);

				system("cls");
			}
		}

		this->setAverageGuess();

		std::cout << "\nResponses:";
		for (int i = 0; i < this->numPlayers; i++) {
			std::cout << (this->playersPtr + i)->getGuess() << ", ";
			(this->playersPtr + i)->setGuessDistFromAverage(this->averageGuess);
		}
		
		this->setRoundWinner();

		std::cout << "\nRound Average: " << this->getAverageGuess();
		std::cout << "\nRound Winner: " << this->roundWinner->getPlayerName();

		std::cout << "\nScore:\n";
		for (int i = 0; i < this->numPlayers; i++) {
			std::cout << (this->playersPtr + i)->getPlayerName() << ": " << (this->playersPtr + i)->getScore() << '\n';
		}


	}

	void startGame() {
		do {
			handleRound();
		} while (!this->finalWinner);

		endGame();
	}

	void endGame() {
		delete[] this->playersPtr;
		this->playersPtr = nullptr;
	}

};

