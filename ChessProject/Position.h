#pragma once

#include <string>

using namespace std;

enum Direction{up = 1, down = -1};

class Position
{
private:
	int row;
	char col;
public:
	Position(string repr); // Throws exception if out of board borders
	~Position();

};
