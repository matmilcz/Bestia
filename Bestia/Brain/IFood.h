#pragma once

class IFood
{
public:
	virtual void eatAnimation() = 0;
    virtual ~IFood() {}
}

class Ham : IFood 
{
public:
	void eatAnimation() 
	{
	}
}

class Water : IFood
{
public:
	void eatAnimation() 
	{
	}
}


class Lollypop : IFood
{
public:
	void eatAnimation() 
	{
	}
}


