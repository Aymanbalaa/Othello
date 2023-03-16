#pragma once
class Position
{
public:
	static const char BLACK = 'B';
	static const char WHITE = 'W';
	static const char EMPTY = ' ';
	static const char UNPLAYABLE = '*';

	virtual bool canPlay() = 0; //polymorphism pure virtual

	virtual Position& move() = 0;
	virtual Position& makeMove(char m) = 0;
	virtual void draw() = 0;

	virtual void setNorth(Position& s) {}
	virtual void setSouth(Position& s) {}
	virtual void setEast(Position& s) {}
	virtual void setWest(Position& s) {}








private:
	char piece;


};

