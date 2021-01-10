#include "buildCalculate.h"

void* CreateCalculate_1() 
{
	ConcreteFactory<CalculateClass, Calculate_1> Factory_1;
	return Factory_1.CreateProduct();
}

void* CreateCalculate_2()
{
	ConcreteFactory<CalculateClass, Calculate_2> Factory_2;
	return Factory_2.CreateProduct();
}

void* CreateCalculate_3()
{
	ConcreteFactory<CalculateClass, Calculate_3> Factory_3;
	return Factory_3.CreateProduct();
}

void* CreateCalculate_4()
{
	ConcreteFactory<CalculateClass, Calculate_4> Factory_4;
	return Factory_4.CreateProduct();
}

void* CreateCalculate_5()
{
	ConcreteFactory<CalculateClass, Calculate_5> Factory_5;
	return Factory_5.CreateProduct();
}

buildCalculate::buildCalculate() 
{
	relationship['1'] = CreateCalculate_1;
	relationship['2'] = CreateCalculate_2;
	relationship['3'] = CreateCalculate_3;
	relationship['4'] = CreateCalculate_4;
	relationship['5'] = CreateCalculate_5;
}

buildCalculate::~buildCalculate() {}

int buildCalculate::startCalculate(int num, char sign) 
{
	int c = 0;
	iter = relationship.find(sign);
	if (iter == relationship.end()) 
	{
		throw "没有此功能！";
		return 0;
	}

	pOperation = (CalculateClass*)relationship[sign]();//map能这样调用的逻辑没懂？
	c = pOperation->calculate(num);
	delete pOperation;
	pOperation = NULL;

	return c;
}