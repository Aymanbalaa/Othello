#include <string>

#pragma once
class Player {
public:
	Player();
	Player(std::string n) : name(n) {}
	std::string getName() { return name; }
	void setName(std::string s10) { name = s10; }

private:
	std::string name;
};

