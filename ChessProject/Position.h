#pragma once

#include <string>
#include "Exceptions.h"

using namespace std;

#define MIN_FILE 'a'
#define MAX_FILE 'h'
#define MIN_RANK 1
#define MAX_RANK 8

#define BOARD_SIZE 8

enum Direction{Up = 1, Down = -1};

class Position
{
private:
	char _file; // col
	int _rank; //row
public:
	Position(string repr); // Throws exception if out of board borders
	Position(char file, int rank); // Throws exception if out of board borders
	
	int index() const; // Index in board repr
};
