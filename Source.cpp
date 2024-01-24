//Executable file for Assignment #2 for Engineering Data Structures
//Programming Dice games

//Adding Dependencies
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>


class Dice {
private:
	int numSides;

public:
	int Roll() {
		return int(rand() % 6) + 1;
	}

	Dice(int n) {
		numSides = n;
	}
};

class Player {
private:
	std::string name;
	int score;

public:
	Player(std::string n, int s) {
		
		name = n;
		score = s;
	}
	std::string getName() { return name; };
	int getScore() { return score; };
	void setScore(int num) {score = num;}
};

class DiceGame {
protected:
	
	Player* players;

private:

	std::vector<Player> playerArray;

public:

	Dice myDice;

		virtual void setDice(int n) {
			myDice = Dice(n);
		}

	void initPlayers() {

		int numPlayers;
		std::cout << "How many are playing?" << std::endl;
		std::cin >> numPlayers;

		std::vector<Player> playerArray;

		std::string playerName;
		int playerScore;

		for (int i = 0; i < numPlayers; i++) {

			std::cout << "What is player " << i + 1 << "'s name?" << std::endl;
			std::cin >> playerName;
			std::cout << "What is player " << i + 1 << "'s starting score?" << std::endl;
			std::cin >> playerScore;
			playerArray.push_back(Player(playerName, int(playerScore)));
		}
		players = &playerArray[0];
	};


	void displayScores() {
		for (int i = 0; i < sizeof(playerArray); i++) {

			std::cout << playerArray[i].getName() << " : " << playerArray[i].getScore() << std::endl;
		}
	};
};
int main() {
	//Seeding RNG for consistent output
	srand(static_cast<unsigned>(time(0)));
	
	std::string playerName = "Ben";
	Player myPlayer = Player(std::string("Ben"), 5);

	std::cout << myPlayer.getName() << " " << myPlayer.getScore() << std::endl;
	myPlayer.setScore(17);
	std::cout << myPlayer.getScore();

	return 0;
}