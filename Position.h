#pragma once
class Position
{
public:
	static const char BLACK = 'B';
	static const char WHITE = 'W';
	static const char EMPTY = ' ';
	static const char UNPLAYABLE = '*';

	virtual bool canPlay() = 0; //polymorphism pure virtual

private:
	char piece;


};

