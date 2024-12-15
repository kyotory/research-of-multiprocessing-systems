#pragma once
#include <string>

using namespace std;

class multiprocSystem
{
private:
	int** commands;

	string* memAccess;

	int* workTimeProcessors;

	int Pn; int Kr; int M; int K; int N;

public:
	multiprocSystem(int Pn, int Kr, int M, int K, int N);

	~multiprocSystem();

	void setData();

	void setPn(int newPn);

	void setKr(int newKr);

	void setM(int newM);

	void setK(int newK);

	void setN(int newN);

	int workTime();

	void commutatorWorkImitation();

	void busWorkImitation();

	string memoryAccessCommutator(string request, int num);

	string memoryAccessBus(string request);
};