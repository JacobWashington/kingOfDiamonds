#pragma once
#include "Player.h"

class Round
{
private:
	int roundID;
	int activePlayers;
	double averageGuess;
	int killScore = -10;
	Player* roundWinner = nullptr;
	Player** activePlayersArr = nullptr; 


	void setActivePlayers(int numPlayers, Player* playersPtr) {
		int activePlayers = 0;
		for (int i = 0; i < numPlayers; i++) {
			bool playerLifeStatus = (playersPtr + i)->getLifeStatus();
			if (playerLifeStatus) {
				activePlayers++;
			}
		}

		this->activePlayers = activePlayers;
	}

	void setActivePlayersArr(int numPlayers, Player* playersPtr) {
		this->activePlayersArr = new Player *[this->activePlayers];
		for (int i = 0; i < numPlayers; i++) {
			bool playerLifeStatus = (playersPtr + i)->getLifeStatus();
			if (playerLifeStatus) {
				*(this->activePlayersArr + i) = (playersPtr + i);
			}
		}
	}

	void turns() {
		for (int i = 0; i < this->activePlayers; i++) {
			int guess;

			std::cout << "\n" << (*(this->activePlayersArr + i))->getPlayerName() << ", enter your guess: ";
			std::cin >> guess;
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			(*(this->activePlayersArr + i))->setGuess(guess);

			system("cls");
		}
	}

	void setAverageGuess() {
		double averageGuess = 0.0;

		for (int i = 0; i < this->activePlayers; i++) {
			averageGuess += (*(this->activePlayersArr + i))->getGuess();
		}

		this->averageGuess = (averageGuess / this->activePlayers) * 0.8;
	}

	void adjustPlayerDistFromAverage() {
		for (int i = 0; i < this->activePlayers; i++) {
			(*(this->activePlayersArr + i))->setGuessDistFromAverage(this->averageGuess);
		}
	}

	void setRoundWinner() {
		Player* tempWinner = nullptr;
		for (int i = 0; i < this->activePlayers; i++) {
			if (tempWinner) {
				Player nextPlayer = *(*this->activePlayersArr + i);
				std::cout << "\nNEXTPLAYER " << nextPlayer.getPlayerName();
				if (tempWinner->getDistFromAverage() > nextPlayer.getDistFromAverage()) {

					tempWinner->setScore(-1);
					tempWinner = (*(this->activePlayersArr + i));

				}
				else {
					(*(this->activePlayersArr + i))->setScore(-1);
				}
			}
			else {
				tempWinner = (*(this->activePlayersArr + i));
			}
		}

		this->roundWinner = tempWinner;
	}

	void showResults() {
		system("cls");

		std::cout << "\nPlayer Guesses: ";
		for (int i = 0; i < this->activePlayers; i++) {
			if (i == (this->activePlayers - 1)) {
				std::cout << (*(this->activePlayersArr + i))->getGuess() << '\n';
			}
			else {
				std::cout << (*(this->activePlayersArr + i))->getGuess() << ", ";
			}
		}

		std::cout << "\nRound Average: " << this->getAverageGuess() << '\n';

		std::cout << "\nWINNER: " << this->getRoundWinner()->getPlayerName() << '\n';

		std::cout << "\nSCORE:\n";
		for (int i = 0; i < this->activePlayers; i++) {
			std::cout << (*(this->activePlayersArr + i))->getPlayerName() << ": ";
			std::cout << (*(this->activePlayersArr + i))->getScore() << '\n';
		}

		for (int i = 0; i < this->activePlayers; i++) {
			if ((*this->activePlayersArr + i)->getScore() == this->killScore) {
				(*this->activePlayersArr + i)->setLifeStatus();
				std::cout << '\n' << (*this->activePlayersArr + i)->getPlayerName() << "'s score is -10. "
					<< "Player is ELIMINATED.\n";
			}
		}

		system("pause");
		system("cls");
	}
	
public:

	Round(int roundNum, int numPlayers, Player* playersPtr, Player* finalWinner) {
		this->roundID = roundNum;
		this->setActivePlayers(numPlayers, playersPtr);
		this->setActivePlayersArr(numPlayers, playersPtr);
		if (this->activePlayers > 1) {
			std::cout << "\n****** ROUND " << this->roundID << " ******\n";
			this->turns();
			this->setAverageGuess();
			this->adjustPlayerDistFromAverage();
			this->setRoundWinner();
			this->showResults();
		}
		else {
			finalWinner = *(this->activePlayersArr);
		}
	}

	double getAverageGuess() {
		return this->averageGuess;
	}

	Player* getRoundWinner() {
		return this->roundWinner;
	}

	void endRound() {
		delete[] this->activePlayersArr;
		this->activePlayersArr = nullptr;
		this->roundWinner = nullptr;
	}
};

