//Facebook Trail - main

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <time.h>

#include "charles.cpp"
#include "sam.cpp"

using namespace std;


class masterClass {

public:
	nameStore masterNameStore;
	Inventory masterInventory;
	map worldMap;
	vector <Person> masterPerson;

	masterClass(nameStore newNm, string *partyPtr ) {
		masterNameStore = newNm;

		for (int i = 0; i < 5; i++)
		{
			masterPerson.push_back(Person());
			masterPerson[i].setName(*(partyPtr + i));
		}

	}

};

void openMenu(mapSquare location, masterClass master);

void selectEvent(mapSquare location, masterClass master) {
	string tileName = location.getName();
	srand(time(0));

	if (tileName == "Forest") {
		//60%
		int rande = rand() % 10;

		if (rande <= 6) {
			//execute encounter
			randomEvent1(master.masterPerson, master.masterInventory);
			system("pause");
		}
		else {
			openMenu(location, master);
		}
	}
	else if (tileName == "Open Grass") {
		//50%
		int rande = rand() % 10;

		if (rande <= 5) {
			//execute encounter
			randomEvent1(master.masterPerson, master.masterInventory);
			system("pause");
		}
		else {
			openMenu(location, master);
		}
	}
	else if (tileName == "Vilage") {
		//30%
		int rande = rand() % 10;

		if (rande <= 3) {
			//execute encounter
			randomEvent1(master.masterPerson, master.masterInventory);
			system("pause");
		}
		else {
			openMenu(location, master);
		}
	}
	else if (tileName == "Path") {
		//20%
		int rande = rand() % 10;

		if (rande <= 2) {
			//execute encounter
			randomEvent1(master.masterPerson, master.masterInventory);
			system("pause");
		}
		else {
			openMenu(location, master);

		}
	}
	else if (tileName == "Safe House") {
		eventSet2(master.masterPerson, master.masterInventory);
		openMenu(location, master);
	}
	else if (tileName == "Home") {
		//open home
	}
	else if (tileName == "End") {
		//play ending
		eventSet3(master.masterPerson, master.masterInventory);
	}
}

void waitForPlayer() {
	//cout << "Press enter to continue..." << endl;
	//string tmp;
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	system("pause");
	cout << endl;
}

void scavange(mapSquare location, masterClass master) {
	cout << "You and your party wonder round the area looking for food and items..." << endl << "After a while:" << endl;

	int odds;
	string n = location.getName();

	if (n == "Open Grass")
		odds = 3;
	else if (n == "Forest")
		odds = 3;
	else if (n == "Vilage")
		odds = 6;
	else if (n == "Path")
		odds = 2;
	else if (n == "Safe House")
		odds = 10;
	else
		odds = 2;

	srand(time(0));
	int rande = rand() % 10;

	if (rande < odds) {
		master.masterInventory.changeNumOfRations(5 * rande);
		master.masterInventory.changeNumOfBandages(rande);
		cout << "You stumble-upon " << 5 * rande << " portions of food and " << rande << " bandages" << endl;

	}
	else if (rande == 0) {
		//hurt someone!!
		rande = (rand() % 5);
		cout << master.masterPerson[rande].getName() << " falls down and cracks their arm on the hard ground (-25 health)" << endl;
		master.masterPerson[rande].changeHealth(-25);
	} else {
		cout << "You re-group empty handed..." << endl;
	}




}

void openMenu(mapSquare location, masterClass master) {
	bool exit = false;

	if (master.masterPerson[0].getHealth() <= 0) {
		exit = true;
		gameOver();
	}


	while (!exit) {
		cout << "Choice 1: Move" << endl;
		cout << "Choice 2: Heal-up" << endl;
		cout << "Choice 3: Scavange for suplies" << endl;
		cout << "Choice 4: Check-on Party" << endl;
		cout << "Choice 5: Check Inventory" << endl;

		int choice = getUserChoice(1, 5);
		system("CLS");
		switch (choice) {
		case 1:
			location = master.worldMap.move();
			selectEvent(location, master);
			break;
		case 2:
			//healup function
			cout << "Who would you like to heal up?" << endl;
			cout << "1: " << master.masterPerson[0].getName() << endl;
			cout << "2: " << master.masterPerson[1].getName() << endl;
			cout << "3: " << master.masterPerson[2].getName() << endl;
			cout << "4: " << master.masterPerson[3].getName() << endl;
			cout << "5: " << master.masterPerson[4].getName() << endl;

			choice = getUserChoice(1, 5);
			
			cout << "Healing " << master.masterPerson[choice - 1].getName() << " (-1 bandages)" << endl;
			master.masterInventory.changeNumOfBandages(-1);
			master.masterPerson[choice - 1].changeHealth(10);
			waitForPlayer();
			break;
		case 3:
			scavange(location, master);
			waitForPlayer();
			break;
		case 4:
			displayPeople(master.masterPerson);
			waitForPlayer();
			break;
		case 5:
			cout << "Your inventory contains: " << endl;
			master.masterInventory.printInventory();
			waitForPlayer();
			break;
		default:
			cout << "Well, isn't that just silly?" << endl;
			break;
			
		}
		
		system("CLS");
	}
}

void newGame() {
	srand(time(0));

	system("CLS");

	splashScreen();
	gameIntro();
	nameStore theNameStore = getGameNames();
	masterClass master = masterClass(theNameStore, theNameStore.getPartyPtr());


	system("CLS");
	//game starts
	eventSet1(master.masterPerson, master.masterInventory);
	openMenu(master.worldMap.getOrigin(), master);
}

void gameOver()
{
	cout << "Unfortunately, you died\n\n\nGAME OVER!" << endl;
	waitForPlayer();

}

int main()
{
	
	newGame();

	//eventSet1(personVector, inventory);  //Home
	//eventSet2(personVector, inventory);  //Safe Zone
	//eventSet3(personVector, inventory);  //End

	return 0;
}  //End main