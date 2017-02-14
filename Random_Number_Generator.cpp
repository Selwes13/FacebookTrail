//My Awesome Program!

#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int randNum;

	for (int i = 0; i <= 50; i++)
	{
		int randNum = (rand() % 20) + 1;
		cout << "Random number: " << randNum << endl;
	}

	return 0;
}