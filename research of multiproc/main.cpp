#include <iostream>
#include "multiprocSystem.h"

#define DEFAULT_CHOICE 1

using namespace std;

static void userInterface()
{
	system("cls");

	int Pn, Kr, M, K, N;
	char choice = DEFAULT_CHOICE;

	cout << "Write a number of the processors and memory blocks (N): ";
	cin >> N;
	cout << endl << "Write a percent of the data, using in one memoryblock (Pn): ";
	cin >> Pn;
	cout << endl << "Write a percent of the commands, that aren't using external memory (Kr): ";
	cin >> Kr;
	cout << endl << "Write a unit of time for commands with the memory request (M): ";
	cin >> M;
	cout << endl << "Write a number of the commands (K): ";
	cin >> K;

	multiprocSystem target(Pn, Kr, M, K, N);
	target.setData();

	target.commutatorWorkImitation();
	target.busWorkImitation();
}

int main()
{
	char tryChoice = DEFAULT_CHOICE;

	while (true)
	{
		userInterface();
		cout << endl << "Do you want to change the values and try again? (Y/N): ";
		cin >> tryChoice;

		if (tryChoice == 'Y' || tryChoice == 'y') continue;

		else if (tryChoice == 'N' || tryChoice == 'n') break;

		else cout << endl << "Unknown command. Program will be shutted down" << endl; break;
	}

	return 0;
}