//Executable file for Assignment #2 for Engineering Data Structures
//Programming Dice games

//Adding Dependencies
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>

using namespace std;

class Dice {
private:

	int numSides;

public:
	int Roll() {
		return int(rand() % 6) + 1;
	}

	Dice() { numSides = 6; }
	Dice(int n) {
		numSides = n;
	}
};

class Player {
private:
	string name;
	int score;

public:
	Player(string n, int s) {

		name = n;
		score = s;
	}
	string getName() { return name; };
	int getScore() { return score; };
	void setScore(int num) { score = num; }
};

class DiceGame {
protected:

	Player* players;

private:



public:

	vector<Player> playerArray;
	int numDice;
	Dice myDice;

	//
	//DiceGame(int numPlayer, int numDice, int numSides, std::string gameName) {
		//if (gameName == "Boston") { BostonDiceGame(numPlayer, numDice, numSides); }

		//else if (gameName == "Knockout") { KnockOut(numPlayer, numDice, numSides); }
		//else {
			//std::cout << "You have selected an invalid game type motherfucker" << std::endl;
			//return;
		//}
	//}
	void setDice(int num, int sides) {
		myDice = Dice(sides);
		numDice = num;
	}

	void initPlayers(int numPlayers) {

		//Redeclaring and clearing any pre-existing playerArray
		//std::vector<Player> playerArray;

		//Initializing variables to hold individual player names and scores
		string playerName;
		int playerScore;

		//Looping <numPlayers> times to individually create players
		for (int i = 0; i < numPlayers; i++) {

			//Requesting and storing player <i +1>'s name and starting score
			cout << "What is player " << i + 1 << "'s name?" << endl;
			cin >> playerName;
			cout << "What is player " << i + 1 << "'s starting score?" << endl;
			cin >> playerScore;

			//Using .push_back() to add a new Player to the playerArray
			playerArray.push_back(Player(playerName, int(playerScore)));
		}

		//Storing the pointer of the first player in the playerArray
		players = &playerArray[0];
	};
	void displayScores() {

		//Looping for every player in playerArray
		for (int i = 0; i < size(playerArray); i++) {

			//Displaying an individual players name and score as "<Player [i]'s name> : <Player [i]'s score> 
			cout << playerArray[i].getName() << " : " << playerArray[i].getScore() << endl;
		}
	};
	void writeScoresToFile() {

		ofstream scorefile;
		scorefile.open("Scorecard.txt", ios::out | ios::app);
		for (int i = 0; i < size(playerArray); i++) { scorefile << playerArray[i].getName() << ":" << playerArray[i].getScore() << endl; }
	}

	Player getHighestScore() {

		ifstream scorefile("Scorecard.txt");
		if (!scorefile.is_open()) {
			cerr << "File does not exist, or was not able to open" << endl;
			return Player("No one", 0);
		}

		vector<string> names;
		vector<int> scores;
		string score;

		while (!scorefile.eof()) {
			names.push_back("");
			getline(scorefile, names[size(names) - 1], ':');
			scorefile >> score;
			scores.push_back(atoi(score.c_str()));
		}

		int highScore = 0;
		string bestPlayer{};

		for (int i = 0; i < size(scores); i++) {
			if (highScore < scores[i]) {
				highScore = scores[i];
				bestPlayer = names[i];
			}
		}
		return Player(bestPlayer, highScore);
	}
	virtual void play() = 0;

};

class KnockOut : public DiceGame {
protected:


private:


public:

	KnockOut(int numPlayers, int numDice, int numSides) {

		setDice(numDice, numSides);
		initPlayers(numPlayers);


	}
	int rollDice() {

		int rollAmount = 0;

		for (int i = 0; i < numDice; i++) {
			rollAmount += myDice.Roll();
		}
		return rollAmount;
	}

	void play() {

		//Determining the target score by rolling <myDice> <numDice> times
		int targetScore = rollDice();

		//Printing first line of the game, showing the
		cout << "Welcome to Knock out! The target score is: " << targetScore << endl;

		//Initializing a copy of the playerArray, to store all remaining players
		vector<Player> remainingPlayers = playerArray;

		//Setting an index to reference which player's turn it is
		int currentPlayer = 0;

		while (remainingPlayers.size() > 1) {

			int playerRoll = rollDice();

			cout << "It is " << remainingPlayers[currentPlayer].getName() << "'s Turn! " << remainingPlayers[currentPlayer].getName() << " has rolled: " << playerRoll << endl;


			if (playerRoll == targetScore) {
				cout << remainingPlayers[currentPlayer].getName() << " has been eliminated!" << endl;
				remainingPlayers.erase(remainingPlayers.begin() + currentPlayer);

				//Handling an edge case where the last player in the array is eliminated
				currentPlayer = currentPlayer % remainingPlayers.size();

				//Might need a statement to handle reassigning the pointer variable if the first player eliminated
			}
			else {
				//If no player eliminated, increment current player and use % to stay within valid array index
				currentPlayer = (currentPlayer + 1) % remainingPlayers.size();
			}

		}
		cout << remainingPlayers[0].getName() << " has won Knockout! You have been awarded " << targetScore << " points!" << endl;

		for (int i = 0; i < size(playerArray); i++) {
			if (playerArray[i].getName() == remainingPlayers[0].getName()) {
				playerArray[i].setScore(playerArray[i].getScore() + targetScore);
				return;
			}
		}
	}
};

class BostonDiceGame : public DiceGame {
protected:

private:

public:


	BostonDiceGame(int numPlayers, int numDice, int numSides) {

		setDice(numDice, numSides);
		initPlayers(numPlayers);

	};

	//This function returns the highest value from a series of die rolls
	//The highest roll from each iteration is returned, and the play() logic
	//will repeatedly call this to generate a vector one entry at a time
	int rollDiceHighest(int numRolls) {

		//Initializing variable to store highest roll locally
		int highestRoll = 0;

		//Looping <numRolls> times
		for (int i = 0; i < numRolls; i++) {

			highestRoll = max(highestRoll, myDice.Roll());
		}
		return highestRoll;
	}

	void play() {

		cout << "Welcome to Boston Dice Game! " << endl;

		//Looping among all players in playerArray
		cout << size(playerArray) << "This is a test" << endl;
		for (int i = 0; i < size(playerArray); i++) {

			//Declaring an integer score to store an individual player's score
			int playerScore = 0;

			//Printing the current player's turn
			cout << "It is Player " << i + 1 << "'s Turn!" << endl;

			//Looping numDice times to generate the score one round at a time
			for (int rollnum = 0; rollnum < numDice; rollnum++) {

				//Calling rollDiceHighest() to return the highest value roll each round
				int newRoll = rollDiceHighest(numDice - rollnum);

				//Incrementing playerScore
				playerScore += newRoll;

				//Printing the rolled value and current round score
				cout << "Round " << rollnum + 1 << ": Highest roll is " << newRoll << ". Score is now: " << playerScore << endl;

			}

			//Storing the player's score in the array
			playerArray[i].setScore(playerScore);
		}

		//Determining the winner by highest score value.
		int highestScore = 0;
		int winnerIndex = 0;

		for (int i = 0; i < size(playerArray); i++) {
			if (max(highestScore, playerArray[i].getScore()) == playerArray[i].getScore()) {
				highestScore = max(highestScore, playerArray[i].getScore());
				winnerIndex = i;
			}
		}

		//Checking for the case of a tie. NO WINNERS IN A TIE
		for (int i = 0; i < winnerIndex; i++) {
			if (highestScore == playerArray[i].getScore()) {


				cout << "There is a tie! There are no winners :(" << endl;
				return;
			}
		}
		cout << "The winner is " << playerArray[winnerIndex].getName() << "!" << endl;
	}
};
int main() {
	//Seeding RNG for consistent output
	srand(static_cast<unsigned>(time(0)));

	KnockOut newKnockOutGame = KnockOut(4, 3, 6);
	newKnockOutGame.play();
	newKnockOutGame.displayScores();

	newKnockOutGame.writeScoresToFile();
	Player highScorePlayer = newKnockOutGame.getHighestScore();

	cout << highScorePlayer.getName() << " has a highscore of " << highScorePlayer.getScore() << "!\n";

	return 0;
}
