#pragma once
#include "IFood.h"
#include <algorithm>

class Hunger 
{
	Hunger() : hunger(0) {}
	void increase() { ++hunger; }
	void decrease() { --hunger; }
	unsigned getHunger() { return hunger; }

private:
	unsigned hunger;
};

class Fun 
{
	Fun() : fun(0) {}
	void increase() { ++fun; }
	void decrease() { --fun; }
	unsigned getFun() { return fun; }

private:
	unsigned fun;
};

class Condition
{
public:
	void checkFun(Fun& fun) 
	{
		if (fun.getFun() == 0) 
		{
			// Bestia is seak
		}
		else 
		{
			//Bestia is happy
		}
	}
	void checkHunger() 
	{
		if (fun.getFun() == 0)
		{
			// Bestia is dead
		}
		else
		{
			//Bestia is happy
		}
	}
};

class IGame 
{
};

class Brain 
{
	Brain(Hunger hunger, Fun fun) {}
public:
	void eat(IFood p_food) { hunger.increase(); }
	void play(IGame p_game) { fun.increase(); }

};