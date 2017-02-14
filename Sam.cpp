#include <iostream>
#include <string>
#include <time.h>
//#include "main.cpp"
//includes mapping, moving, getting names
using namespace std;


class mapSquare {
	

public: string name;
public: bool passable;

	mapSquare(string tileName, bool traversable) {
		name = tileName;
		passable = traversable;
	}

public: bool getPassable() { return passable; }
		string getName() { return name; }
};

class map {
	int playerX = 0, playerY = 0;

	//Path, Open Grass, Forest, Vilage, Safe House, Home, End
	mapSquare worldMap[10][10] = { 
								{ mapSquare("Home", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Open Grass", true), mapSquare("Path", true), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Vilage", true) },
								{ mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Forest", true) },
								{ mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Forest", true) },
								{ mapSquare("Open Grass", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Path", true), mapSquare("Path", true) },
								{ mapSquare("Open Grass", true), mapSquare("Vilage", true), mapSquare("Open Grass", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Path", true), mapSquare("Open Grass", true) },
								{ mapSquare("Path", true), mapSquare("Path", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Safe House", true), mapSquare("Open Grass", true) },
								{ mapSquare("Path", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("River", false), mapSquare("River", false), mapSquare("River", false), mapSquare("River", false), mapSquare("River", false), mapSquare("River", false) },
								{ mapSquare("Path", true), mapSquare("River", false), mapSquare("River", false), mapSquare("River", false), mapSquare("River", false), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Path", true) },
								{ mapSquare("Path", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Vilage", true), mapSquare("Forest", true), mapSquare("Path", true), mapSquare("Open Grass", true), mapSquare("Path", true) },
								{ mapSquare("Safe House", true), mapSquare("Path", true), mapSquare("Path", true), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Forest", true), mapSquare("Open Grass", true), mapSquare("Open Grass", true), mapSquare("End", true) }
	};
	
	
	bool validDir[4] = { true, true, true, true };
	bool *dirPtr = validDir;
	//constructor

	int getUserChoice(int min, int max)
	{
		//Enter choice
		static int userChoice = 0;

		//Check if userChoice is valid (integer between 1 and 4)
		cout << "Enter your choice (" << min << " - " << max << "): ";
		cin >> userChoice;
		while ((userChoice < min) || (userChoice > max))
		{
			//Get input from user
			cout << "\nIncorrect choice\n" << endl;
			cout << "Enter your choice (1-4): ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> userChoice;
		}
		return userChoice;
	}

	void checkDirections(bool *output) {
		//NESW
		
		//north
		if (playerY == 0)
			*output = false;
		else if (!worldMap[playerY - 1][playerX].getPassable())
			*output = false;
		else
			*output = true;
		
		output++;

		//east
		if (playerX == size(worldMap) - 1)
			*output = false;
		else if (!worldMap[playerY][playerX + 1].getPassable())
			*output = false;
		else
			*output = true;
		
		output++;

		//south
		if (playerY == size(worldMap[0]) - 1)
			*output = false;
		else if (!worldMap[playerY + 1][playerX].getPassable())
			*output = false;
		else
			*output = true;

		output++;
		
		//west
		if (playerX == 0)
			*output = false;
		else if (!worldMap[playerY][playerX - 1].getPassable())
			*output = false;
		else
			*output = true;
			
	}

	string intToDir(int i) {
		string out = "";
		switch (i) {
		case 0:
			out = "North \t^";
			break;
		case 1:
			out = "East \t>";
			break;
		case 2:
			out = "South \t\\/";
			break;
		case 3:
			out = "West \t<";
			break;
		default:
			out = "no dir " + i;
			break;
		}
		return out;
	}

	mapSquare moveDir(int i) {
		mapSquare out = mapSquare("err", false);
		//cout << "moving dir(" << i << ") from (" << playerX << ", " << playerY;
		switch (i) {
		case 0:
			playerY--;
			break;
		case 1:
			playerX++;
			break;
		case 2:
			playerY++;
			break;
		case 3:
			playerX--;
			break;
		default:
			cout << "no dir " << i << endl;
			break;
		}
		cout << ") to (" << playerX << ", " << playerY << ")" << endl;
		out = worldMap[playerY][playerX];

		return out;
	}

	string getTileType(int i) {
		
		switch (i) {
		case 0:
			return worldMap[playerY - 1][playerX].getName();
			break;
		case 1:
			return worldMap[playerY][playerX + 1].getName();
			break;
		case 2:
			return worldMap[playerY + 1][playerX].getName();
			break;
		case 3:
			return worldMap[playerY][playerX - 1].getName();
			break;
		default:
			return worldMap[playerY][playerX].getName();
			break;
		}
		
		return worldMap[playerY][playerX].getName();
	}

public: mapSquare move() {
		//cout << "x: " << playerX << "y: " << playerY << endl;
		
		//cout << "Player X: " << playerX << " Player Y: " << playerY << " into " << worldMap[playerY][playerX].getName() << endl;
		//cout << "\t" << *dirPtr << endl;
		//cout << *(dirPtr + 3) << "\t\t" << *(dirPtr + 1) << endl;
		//cout << "\t" << *(dirPtr + 2) << endl;

		int j = 1;
		int choiceRelay[]{ -1, 1, 2, 3, 4 };
		bool *ptr = validDir;
		//cout << validDir[0] << validDir[1] << validDir[2] << validDir[3] << endl;
		checkDirections(ptr);
		//finds possible directions and shows them
		/*
		for (int i = 0; i < 4; i++) {
			if (validDir[i]) {
				cout << "Choice " << j << ": Go " << intToDir(i) << " into " << getTileType(i) << endl;
				choiceRelay[j] = i;
				j++;
			}
		}
		j--;
		
		int choice = getUserChoice(1, j);
		choice = choiceRelay[choice];
		*/
		for (int i = 0; i < 4; i++) {
			if (validDir[i]) {
				cout << "Choice " << i+1 << ": Go " << intToDir(i) << " into " << getTileType(i) << endl;
			}
			else {
				cout << "Choice " << i+1 << ": -" << endl;
			}
		}

		int choice;
		do {
			choice = getUserChoice(1, 4);
		} while (!validDir[choice - 1]);

		system("CLS");
		

		cout << "Moving " << intToDir(choice - 1) << " into " << worldMap[playerY][playerX].getName()<< endl << endl;
		moveDir(choice - 1);

		return worldMap[playerY][playerX];
	}

	void displayMap() {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				if (x == playerX && y == playerY)
					cout << "P";
				else 
					cout << worldMap[y][x].getPassable();
				
			}
			cout << endl;
		}
	}

	mapSquare getOrigin() { return worldMap[0][0]; }
};

class nameStore {

	string partyNames[5], raiders[2], crazyPerson, shopKeeper;

	int randomDelay[9], randomDelayV1[9] = { 0, 5, 8, 1, 6, 2, 4, 7, 3 }, randomDelayV2[9] = { 0, 3, 5, 6, 7, 8, 4, 2, 1 };

public: 
	nameStore(string *ptr) {
		srand(time(0));
		if (rand() % 2 == 0) {
			for (int i = 0; i < 9; i++) {
				randomDelay[i] = randomDelayV1[i];
			}
		}
		else {
			for (int i = 0; i < 9; i++) {
				randomDelay[i] = randomDelayV2[i];
			}
		}

		for (int i = 0; i < 5; i++) {
			partyNames[i] = *(ptr + randomDelay[i]);
		}

		raiders[0] = *(ptr + randomDelay[5]);
		raiders[1] = *(ptr + randomDelay[6]);

		crazyPerson = *(ptr + randomDelay[7]);

		shopKeeper = *(ptr + randomDelay[8]);

	}

		nameStore() {

		}

	string* getPartyPtr() { 
		string *temp = partyNames;
		return temp;
	}
	
	void displayAllNames() {
		for (int i = 0; i < 5; i++) {
			cout << partyNames[i] << endl;
		}
		cout << raiders[0] << endl;
		cout << raiders[1] << endl;

		cout << crazyPerson << endl;
		cout << shopKeeper << endl;
	}

	
};

nameStore getGameNames() {

	string in, theArray[9];

	for (int i = 0; i < 9; i++) {
		if (i == 0)
			cout << "Enter your name, player: " << endl;
		else
			cout << "Enter " << 9 - i << " more friends names: " << endl;
		
		cin >> in;

		if (in == "---") {
			theArray[0] = "Tracy";
			theArray[1] = "Bob";
			theArray[2] = "Harry";
			theArray[3] = "Peete";
			theArray[4] = "Sam";
			theArray[5] = "Ross";
			theArray[6] = "Chad";
			theArray[7] = "Michale";
			theArray[8] = "Jean-Paul";
			break;

		}


		theArray[i] = in;
	}
	
	string *ptr = theArray;
	nameStore theNameStore = nameStore(ptr);
	//theNameStore.displayAllNames();
	return theNameStore;
}


/*
int main() {
	system("CLS");
	//getGameNames();

	
	map newMap;

	while (true) {
		newMap.displayMap();
		newMap.move();

	}
	
	return 0;
}
*/