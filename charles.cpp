//charles-classes

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>


using namespace std;

void gameOver();

class Person
{
	string name;
	int health, age, nutrition;
	static int numberOfPeople;
	bool isDead = false;
	bool isBitten = false;
public:
	//Getters
	string getName() { return name; }
	int getHealth() { return health; }
	int getAge() { return age; }
	int getNutrition() { return nutrition; }
	static int getNumberOfPeople() { return numberOfPeople; }
	bool getDeadState() { return isDead; }

	//Setters
	void setName(string newName) { name = newName; }
	void setHealth(int newHealth) { health = newHealth; }
	void setAge(int newAge) { age = newAge; }
	void setNutrition(int newNutrition) { nutrition = newNutrition; }

	//Constructor
	Person();

	//Main functions
	void printAllDetails()  //Prints all details of a person
	{
		cout << "Name: " << name << "\n    Age: " << age << "\n    Health: " << health <<  "\n    Nutrition: " << nutrition << "\n" << endl;
	}

	void printDeadDetails()  //Print details of dead person
	{
		cout << "Name: " << name << "\n    Age: " << age << "\n" << endl;
	}

	void killPerson()  //Kill a person
	{
		name += " (DEAD)";
		health = 0;
		nutrition = 0;
		isDead = true;
	}

	void changeHealth(int amount)  //Change health
	{
		health = health + amount;
		if (health > 100)
		{
			health = 100;
		}
	}

	void changeNutrition(int amount)  //Change nutrition
	{
		nutrition = nutrition + amount;
		if (nutrition > 100)
		{
			nutrition = 100;
		}
	}
};  //End of Person class

int Person::numberOfPeople = 0;

//Constructor
Person::Person()
{
	numberOfPeople++;
	age = (rand() % 20) + 17;
	health = (rand() % 20) + 80;
	nutrition = (rand() % 20) + 80;
}

class Inventory
{
	private:
		int numOfBandages, numOfRations;

	public:
		//Getters
		int getNumOfBandages() { return numOfBandages; }
		int getNumOfRations() { return numOfRations; }

		//Setters
		void setNumOfBandages(int newNumOfBandages) { numOfBandages = newNumOfBandages; }
		void setNumOfRations(int newNumOfRations) { numOfRations = newNumOfRations; }

		//Constructor
		Inventory();

		//Main functions
		void changeNumOfBandages(int amount)  //Change number of bandages
		{
			numOfBandages = numOfBandages + amount;
		}

		void changeNumOfRations(int amount)  //Change number of rations
		{
			numOfRations = numOfRations + amount;
		}

		void printInventory()  //Prints all items in inventory
		{
			cout << "\n\n" << endl;
			cout << "Bandages: " << numOfBandages << endl;
			cout << "Rations: " << numOfRations << endl;
			cout << "\n\n" << endl;
		}
};

//Constructor
Inventory::Inventory()
{
	numOfBandages = 2;
	numOfRations = 3;
}

void splashScreen()  //Displays the splash screen (title screen)
{
	cout << "  Welcome to..." << endl;
	cout << "  ______             _                 _      _______        _ _" << endl;
	cout << " |  ____|           | |               | |    |__   __|      (_) |" << endl;
	cout << " | |__ __ _  ___ ___| |__   ___   ___ | | __    | |_ __ __ _ _| |" << endl;
	cout << " |  __/ _` |/ __/ _ \\ '_ \\ / _ \\ / _ \\| |/ /    | | '__/ _` | | |" << endl;
	cout << " | | | (_| | (_|  __/ |_) | (_) | (_) |   <     | | | | (_| | | |" << endl;
	cout << " |_|  \\__,_|\\___\\___|_.__/ \\___/ \\___/|_|\\_\\    |_|_|  \\__,_|_|_|" << endl;
	cout << "\n\n Press enter button to begin..." << endl;
	cin.ignore();
	system("CLS");
}

void gameIntro()  //Displays the intro to the game
{
	cout << "You and a group of 4 friends have just slowly woken up after a night of intense drinking in your latest basement party.\n\n" << endl;
}

void displayPeople(vector <Person>& personVector)
{
	cout << "Your Party:\n" << endl;
	for (int i = 0; i < personVector.size(); i++)
	{
		if (personVector[i].getDeadState() == false)
		{
			personVector[i].printAllDetails();
		}
		else
		{
			personVector[i].printDeadDetails();;
		}
	}
}

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



void event2(vector <Person>& personVector, Inventory& inventory)  //Displays the second event
{
	if (personVector[0].getDeadState() == false)
	{
		//cout << "\nEvent 2:" << endl;
		//displayPeople(personVector);

		//Choices
		cout << "\nYou've just beaten one of your old friends to death, everyone looks at you, searching for answers. You turn on the television and the news is relaying one message, over and over again. The dead have risen, get to the safe zone and whatever you do, do not get bit\n\nAfter the news starts to sink in, you begin to feel a throbbing pain coming from your arm. Upon further inspection, you find it's a bite mark - possibly from your close call with the zombie earlier\n\nIf it's infected, your friends will need to amputate it immediately\n\n" << endl;
		cout << "What do you do?\n" << endl;
		cout << "Choice 1: Let them cut your arm off, you've seen this work in movies but who knows what will happen\n" << "Choice 2: Refuse to let them cut off your arm. You might not be infected and you don't want to lose your favourite arm\n" << endl;

		int userChoice = getUserChoice(1, 2);  //Get choice from user

		system("CLS");  //Clear screen

		int randNumber;

		randNumber = ((rand() % 5) + 1);

		//Find implication of user choice
		switch (userChoice)
		{
		case 1:  //Good
				 //Cut off arm
			cout << "You allow them to cut off your arm" << endl;
			personVector[0].changeHealth(-25);
			cout << "\n\n" << personVector[0].getName() << " lost 25 health\n\n" << endl;
			cout << "After a short while, you are feeling feint from the blood loss, but you don't seem to have turned into a zombie. You're not quite sure if the amputation was neccessary or not, but at least you're still alive... for now\n\n" << endl;
			break;
		case 2:  //Don't cut off arm
			cout << "You are completely sure that you have not been infected and deny the amputation, whether for better or for worse\n" << endl;
			if (randNumber == 1)
			{
				cout << "About an hour passes and you start to feel weird. Your vision is starting to fade and you find it hard to focus. You know instantly what this means. Somehow, you have been infected. Just before you become one of them, you tell your friends to kill you, whilst you are still human. This is the end" << endl;
				cout << "\n\n" << personVector[0].getName() << " is killed by their friends\n\n" << endl;
				personVector[0].killPerson();
			}
			if (randNumber != 1)
			{
				cout << "After what seems like an hour or so, you are still feeling the same as you we're before, but as you know that it takes less that an hour to turn, you are re-assured that you are not infected.\n\n You continue with your journey\n\n" << endl;
			}
			break;
		}
	}  //End if
	else
	{
		gameOver();
	}
	
}  //End of event2

void event1(vector <Person>& personVector, Inventory& inventory)  //Displays the first event
{
	if (personVector[0].getDeadState() == false)
	{
		//cout << "\nEvent 1:" << endl;
		displayPeople(personVector);

		//Choices
		cout << "\nYour alcohol fuelled brain is slowly returning to normal, you are still groggy and as you look up you see one of your friends, a late arrival to your party, he is walking into a wall over and over again and doesn't seem to be reacting to you or your friends\n\n" << endl;
		cout << "What do you do?\n" << endl;
		cout << "Choice 1: Call out their name\n" << "Choice 2: Walk over to them and tap them\n" << "Choice 3: You lose your shit as he looks like a zombie and you scream\n" << "Choice 4: You know this guy is a zombie, you've been binging on zombie films and you know exactly what needs to be done, grab a nearby pipe and hit them over the head\n" << endl;

		int userChoice = getUserChoice(1, 4);  //Get choice from user

		system("CLS");  //Clear screen

		int numOfPeople = Person::getNumberOfPeople();  //Get number of people
		int randPerson = (rand() % numOfPeople);  //Select a random person

		//Find implication of user choice
		switch (userChoice)
		{
		case 1:  //Bad - 50 damage
			cout << "You call their name and it alerts them, they charge and pin you, you hit your head on your way and lose 50 health. You struggle with them and you manage to throw them off you" << endl;
			personVector[randPerson].changeHealth(-50);
			cout << "\n\n" << personVector[randPerson].getName() << " lost 50 health\n\n" << endl;
			break;
		case 2:  //Bad - 25 damage
			cout << "You tap your friend, maybe they are still drunk from last night. They turn and bite you hard on the arm. You lose 25 health" << endl;
			personVector[randPerson].changeHealth(-25);
			cout << "\n\n" << personVector[randPerson].getName() << " lost 25 health\n\n" << endl;
			break;
		case 3:  //Bad - person death
			cout << "As you scream out, it alerts your other sleeping friends, the one closest to the zombie isn’t as lucky as the others and is bitten on the back of his neck as he tries to run, your friend slowly bleeds to death on the ground and you are unable to help him" << endl;
			cout << "\n\n" << personVector[randPerson].getName() << " dies from blood loss\n\n" << endl;
			personVector[randPerson].killPerson();
			break;
		case 4:  //Good
			cout << "You know your shit, all of your life you have waited for this moment, you grab a nearby pipe and you hit your zombie friend on top of the head, a loud crunch follows the blow and they slump to the floor, dead again" << endl;
			cout << "\n\nYou continue unharmed\n\n" << endl;
			break;
		}
	}  //End if
	else
	{
		gameOver();
	}
}  //End event1

/*
void event4(vector <Person>& personVector)  //Displays the forth event
{
	if (personVector[0].getDeadState() == false)
	{
		//cout << "\nEvent 4:" << endl;
		displayPeople(personVector);

		//Choices
		cout << "\nAfter your long and tiresome journey, you finally see the safe zone. As you look around, you see a large shopping mall, it is at least 2 stories tall and the walls have been well fortified, with guards positioned along them. It looks formidable\n\nAs you approach, one of the guards shouts out to you. \"You there, stop, do not come any further. Lay down your weapons and wait for one of the guards to approach you.\"\n\n" << endl;
		cout << "What do you do?\n" << endl;
		cout << "Choice 1: Call out their name\n" << "Choice 2: Walk over to them and tap them\n" << "Choice 3: You lose your shit as he looks like a zombie and you scream\n" << "Choice 4: You know this guy is a zombie, you’ve been binging on zombie films and you know exactly what needs to be done, grab a nearby pipe and hit them over the head\n" << endl;

		int userChoice = getUserChoice(1, 4);  //Get choice from user

		system("CLS");  //Clear screen

		int numOfPeople = Person::getNumberOfPeople();  //Get number of people
		srand(time(0));
		int randPerson = (rand() % numOfPeople);  //Select a random person

		int tempHealth;
		//Find implication of user choice
		switch (userChoice)
		{
		case 1:  //Bad
			cout << "You call their name and it alerts them, they charge and pin you, you hit your head on your way and lose 50 health. You struggle with them and you manage to throw them off you" << endl;
			tempHealth = personVector[randPerson].getHealth();
			personVector[randPerson].setHealth(tempHealth - 50);
			cout << "\n\n" << personVector[randPerson].getName() << " lost 50 health\n\n" << endl;
			break;
		case 2:  //Bad
			cout << "You tap your friend, maybe they are still drunk from last night. They turn and bite you hard on the arm. You lose 25 health" << endl;
			tempHealth = personVector[randPerson].getHealth();
			personVector[randPerson].setHealth(tempHealth - 25);
			cout << "\n\n" << personVector[randPerson].getName() << " lost 25 health\n\n" << endl;
			break;
		case 3:  //Bad
			cout << "As you scream out, it alerts your other sleeping friends, the one closest to the zombie isn’t as lucky as the others and is bitten on the back of his neck as he tries to run, your friend slowly bleeds to death on the ground and you are unable to help him" << endl;
			cout << "\n\n" << personVector[randPerson].getName() << " dies from blood loss\n\n" << endl;
			personVector[randPerson].killPerson();
			break;
		case 4:  //Good
			cout << "You know your shit, all of your life you have waited for this moment, you grab a nearby pipe and you hit your zombie friend on top of the head, a loud crunch follows the blow and they slump to the floor, dead again" << endl;
			cout << "\n\nYou continue unharmed\n\n" << endl;
			break;
		}
	}  //End if
	else
	{
		gameOver();
	}
}  //End event4
*/

void event3(vector <Person>& personVector, Inventory& inventory)  //Displays the third event
{
	if (personVector[0].getDeadState() == false)
	{
		//cout << "\nEvent 3:" << endl;

		//Choices
		cout << "\nAfter your long and tiresome journey, you finally see the safe zone. As you look around, you see a large shopping mall, it is at least 2 stories tall and the walls have been well fortified, with guards positioned along them. It looks formidable\n\nAs you approach, one of the guards shouts out to you. \"You there, stop, do not come any further. Lay down your weapons and wait for one of the guards to approach you.\"\n\nYou and your group lower your weapons to the ground and wait for the guards to escort you into the compound. It doesn't take long for you to be brought into the walls and for the first time in what feels like an eternity, you feel safe from the crazy world outside\n\n" << endl;
		cout << "What do you do?\n" << endl;
		cout << "Choice 1: Gather more supplies\n" << "Choice 2: Rest for the night\n" << "Choice 3: Learn more about the outside world\n" <<  endl;

		int userChoice = getUserChoice(1, 3);  //Get choice from user

		system("CLS");  //Clear screen

		//Find implication of user choice
		switch (userChoice)
		{
		case 1:  //Get supplies
			cout << "You head over to the local shop where they give you free supplies for your journey ahead\n\nYou reveive 2 bandages and 3 rations" << endl;
			inventory.changeNumOfBandages(2);
			inventory.changeNumOfRations(3);
			break;
		case 2:  //Rest party - increase stats
			cout << "You and your party find a place to stay for the night\n\nIn the morning, you are all well rested" << endl;
			cout << "\n\nAll stats increased\n\n" << endl;
			//Increase all stats
			for (int i = 0; i < personVector.size(); i++)
			{
				//Increase health
				personVector[i].changeHealth(30);
				//Increase nutrition
				personVector[i].changeNutrition(35);
			}
			break;
		case 3:  //Learn about world
			cout << "You learn about a group called the 'Knights of Pan'. They are a group of bandits who have covered themselves in various cooking utensils to keep them safe, using the metal as a form of armour. They are as eccentric and insane as their fashion sense. Avoid them at all costs" << endl;
			break;
		}
	}  //End if
	else
	{
		gameOver();
	}
}  //End event3

void randomEvent1(vector <Person>& personVector, Inventory& inventory)
{
	//Choices
	cout << "\nYou encounter a large hoard of zombies travelling in your direction\n\n" << endl;
	cout << "What do you do?\n" << endl;
	cout << "Choice 1: Hide behind the nearest large object\n" << "Choice 2: Run away from the zombies\n" << endl;

	int userChoice = getUserChoice(1, 2);  //Get choice from user

	system("CLS");  //Clear screen

	int randNum = (rand() % 2);
	bool isDamageable = false;;
	int randPerson;

	while (!isDamageable)
	{
		randPerson = (rand() % personVector.size());
		if (personVector[randPerson].getDeadState() == false)
		{
			isDamageable = true;
		}
	}

	//Find implication of user choice
	switch (userChoice)
	{
	case 1:  //Hide behind large object
		if (randNum == 0)  //Good outcome
		{
			cout << "You manage to get hidden just in time as the hoard passes into the distance. Whilst hiding, you spot something on the ground and decide to pick it up" << endl;
			cout << "\n\nYou pick up 1 bandage\n\n" << endl;
			inventory.changeNumOfBandages(1);
		}
		else if (randNum == 1)  //Bad outcome
		{
			cout << "You manage to hide, but you did not spot the zombie coming towards you from behind and it attacks a member of your party" << endl;
			cout << "\n\n" << personVector[randPerson].getName() << " takes 20 damage\n\n" << endl;
			//personVector[randPerson].changeHealth(-20);
			personVector[randPerson].setHealth(personVector[randPerson].getHealth() - 20);
		}
		break;
	case 2:  //Run away
		if (randNum == 0)  //Good outcome
		{
			cout << "The zombies see you, but you manage to outpace them until they are no longer in sight" << endl;
			cout << "\n\nYou got away unharmed this time\n\n" << endl;
		}
		else if (randNum == 0)  //Bad outcome
		{
			cout << "In the hurry to get away, you accidentally drop one of your bandages. Luckilly that's the only thing you lost. This could have gone a lot worse" << endl;
			cout << "\n\nYou lose 1 bandage\n\n" << endl;
			inventory.changeNumOfBandages(-1);
		}
	}
}

/*
void randomEvent2(vector <Person>& personVector, Inventory& inventory)
{

}
*/

void eventSet1(vector <Person>& personVector, Inventory& inventory)
{
	event1(personVector, inventory);
	event2(personVector, inventory);
}

void eventSet2(vector <Person>& personVector, Inventory& inventory)
{
	event3(personVector, inventory);
}


void eventSet3(vector <Person>& personVector, Inventory& inventory)
{
	int randNum = (rand() % 2);

	switch (randNum)
	{
		case 0:
			cout << "The end of your journey is finally here. In front of you is the largest stronghold for humainity within 1000 miles. The tall, magnificent walls of the stronghold stand tall before a golden evening sunset. The only thought that occupies your mind right now is \"It's over. We're safe\"\n\nFor now...." << endl;
			break;
		case 1:
			cout << "As you walk up the hill, the towering walls of the stronghold reveal themselves, showing just what humanity can achieve in the face of such a peril threat. However, as you near you start noticing that something is wrong - all the gates are wide open with nobody in sight. This can only mean bad news. Could this mighty stronghold have fallen so soon after the outbreak occured? It would seem even the gretest of powers can fall in the face of catastrophe. Well, it would seem that your journey is not ready to end yet.\n\nTo be continued..." << endl;
			break;
	
	}
}
