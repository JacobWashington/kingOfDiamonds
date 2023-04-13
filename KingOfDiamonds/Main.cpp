#include <iostream>
#include "Player.h"
using namespace std;

int main() {

	Player* playersPtr = new Player[5];

	for (int i = 0; i < 5; i++) {
		std::cout << '\n' << (playersPtr + i)->getPlayerName();
	}

	delete [] playersPtr;
	playersPtr = nullptr;

	return 0;
}