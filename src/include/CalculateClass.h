#pragma once
class CalculateClass 
{
public:
	virtual int calculate(int num) = 0;
};

class Calculate_1 : public CalculateClass 
{
public:
	int calculate(int num) 
	{
		return num + 1;
	}
};

class Calculate_2 : public CalculateClass
{
public:
	int calculate(int num)
	{
		return num + 3;
	}
};

class Calculate_3 : public CalculateClass
{
public:
	int calculate(int num)
	{
		return num * 2;
	}
};

class Calculate_4 : public CalculateClass
{
public:
	int calculate(int num)
	{
		return num * 3;
	}
};

class Calculate_5 : public CalculateClass
{
public:
	int calculate(int num)
	{
		if (num % 2 == 0) 
		{
			return num / 2;
		}
		else 
		{
			return (num + 1) / 2;
		}
	}
};

