#include <iostream>
#include <time.h>
#include <string>
#include "multiprocSystem.h"

using namespace std;

string procAccess = "DENIED";

multiprocSystem::multiprocSystem(int newPn, int newKr, int newM, int newK, int newN)
{
	Pn = newPn; Kr = newKr; M = newM; K = newK; N = newN;

	memAccess = new string [N];
	workTimeProcessors = new int[N];
	commands = new int* [N];

	for (int i = 0; i < N; i++)
	{
		memAccess[i] = "ALLOWED";
		workTimeProcessors[i] = 0;
		commands[i] = new int[K]();
	}
}

multiprocSystem::~multiprocSystem()
{
	for (int i = 0; i < N; i++)
	{
		delete commands[i];
	}

	delete[] commands;
	delete[] memAccess;
	delete[] workTimeProcessors;
}

void multiprocSystem::setPn(int newPn) { Pn = newPn; }

void multiprocSystem::setKr(int newKr) { Kr = newKr; }

void multiprocSystem::setM(int newM) { M = newM; }

void multiprocSystem::setK(int newK) { K = newK; }

void multiprocSystem::setN(int newN) { N = newN; }

void multiprocSystem::setData()
{
	for (int i = 0; i < N; i++)
	{
		srand(time(NULL) - 100 * i);

		int memoryCommandsCount = K - K * Kr / 100;
		int memoryCommandsBlockCount = memoryCommandsCount * Pn / 100;
		int memoryBlockNumber = 0;

		for (int j = 0; j < K; j++)
		{
			if (memoryCommandsCount && rand() % ((K - j) / memoryCommandsCount) == 0)
			{
				if (memoryCommandsCount - memoryCommandsBlockCount != 0 && rand() % (memoryCommandsCount / (memoryCommandsCount - memoryCommandsBlockCount)) == 0)
				{
					while (true)
					{
						memoryBlockNumber = rand() % N + 1;
						if (memoryBlockNumber != i + 1) break;
					}
				}
				else
				{
					memoryBlockNumber = i + 1;
					memoryCommandsBlockCount--;
				}
				commands[i][j] = memoryBlockNumber;
				memoryCommandsCount--;
			}
			else commands[i][j] = 0;
		}
	}
}

void multiprocSystem::commutatorWorkImitation()
{
	if (M == 0 || N == 0 || K == 0 || Pn == 0 || Kr == 0)
	{
		cout << endl << "Error: Invalid parameters" << endl;
		return;
	}

	cout << endl << "Work time of the system with bus and commutator and info tables: " << endl;

	string access;
	int delay = 1;
	cout << "\n" << "Status" << "\t\t\t" << "Memory request" << "\t" << "Processor" << "\n" << endl;

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (commands[j][i] != 0)
			{
				cout << "Data request" << "\t\tMemory #" << commands[j][i] << "\tProcessor #" << j + 1 << endl;
				while (true)
				{
					access = memoryAccessCommutator("REQUEST", commands[j][i]);
					if (access == "ACCESSED")
					{
						cout << "Memory access" << "\t\tMemory #" << commands[j][i] << "\tProcessor #" << j + 1 << "\t" << endl;
						workTimeProcessors[j] += M;
						break;
					}
					else
					{
						cout << "Memory wait" << "\t\tMemory #" << commands[j][i] << "\tProcessor #" << j + 1 << "\t" << endl;
						workTimeProcessors[j] += 1 * delay;
						delay++;
						memoryAccessCommutator("FREE", commands[j][i]);
					}
				}
			}
			else
			{
				workTimeProcessors[j] += 1;
				cout << "No memory request" << "\t-" << "\t\tProcessor #" << j + 1 << "\t" << endl;
			}
		}
		for (int i = 0; i < N; i++)
		{
			memAccess[i] = "ALLOWED";
		}
		delay = 1;
	}

	cout << endl << "Commutator work time - " << workTime() << "\n\n-------------------------------------------------------\n";
}

void multiprocSystem::busWorkImitation()
{
	if (M == 0 || N == 0 || K == 0 || Pn == 0 || Kr == 0) return;

	string access;
	int delay = 1;
	cout << endl << "Status" << "\t\t\t" << "Memory request" << "\t" << "Processor" << endl << endl;

	for (int i = 0; i < K; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (commands[j][i] != 0)
			{
				cout << "Data request" << "\t\tMemory #" << commands[j][i] << "\tProcessor #" << j + 1 << "\t" << endl;
				while (true)
				{
					access = memoryAccessBus("REQUEST");
					if (access == "ACCESSED")
					{
						cout << "Memory access" << "\t\tMemory #" << commands[j][i] << "\tProcessor #" << j + 1 << "\t" << endl;
						workTimeProcessors[j] += M;
						break;
					}
					else
					{
						cout << "Memory wait" << "\t\tMemory #" << commands[j][i] << "\tProcessor #" << j + 1 << "\t" << endl;
						workTimeProcessors[j] += 1 * delay;
						delay++;
						memoryAccessBus("FREE");
					}
				}
			}
			else
			{
				workTimeProcessors[j] += 1;
				cout << "No memory request" << "\t-" << "\t\tProcessor #" << j + 1 << "\t" << endl;
			}
		}
		delay = 1;
	}

	cout << endl << "Bus work time - " << workTime() << endl;
}

string multiprocSystem::memoryAccessCommutator(string request, int num)
{
	procAccess = memAccess[num - 1];

	if (procAccess == "ALLOWED" && request == "REQUEST")
	{
		procAccess = "DENIED";
		memAccess[num - 1] = "DENIED";
		return "ACCESSED";
	}

	else if (procAccess == "DENIED" && request == "REQUEST")
	{
		return "DENIED";
	}

	else if (procAccess == "DENIED" && request == "FREE")
	{
		procAccess = "ALLOWED";
	}

	memAccess[num - 1] = "ALLOWED";
	return procAccess;
}

string multiprocSystem::memoryAccessBus(string request)
{
	if (procAccess == "ALLOWED" && request == "REQUEST")
	{
		procAccess = "DENIED";
		return "ACCESSED";
	}

	else if (procAccess == "DENIED" && request == "FREE")
	{
		procAccess = "ALLOWED";
	}

	return procAccess;
}

int multiprocSystem::workTime()
{
	int maxTime = 0;

	for (int i = 0; i < N; ++i)
	{
		if (workTimeProcessors[i] > maxTime) maxTime = workTimeProcessors[i];
	}

	return maxTime;
}