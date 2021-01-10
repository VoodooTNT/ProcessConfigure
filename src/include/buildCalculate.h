#pragma once
#include <map>
#include "templateFactory.h"
#include "CalculateClass.h"

using namespace std;

typedef void* (*PTRCreateClass)(void);

class buildCalculate 
{
public:
	buildCalculate();
	~buildCalculate();

public:
	int startCalculate(int num, char sign);

public:
	map<char, PTRCreateClass> relationship;
	map<char, PTRCreateClass>::iterator iter;
	CalculateClass *pOperation;
};