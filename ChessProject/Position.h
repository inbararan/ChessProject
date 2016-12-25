#pragma once

#include <string>

using namespace std;

#define MIN_RANK 1
#define MAX_RANK 8
#define MIN_FILE 'a'
#define MAX_FILE 'h'

#define BOARD_SIZE 8

enum Direction{Up = 1, Down = -1};

class Position
{
private:
	int rank; //row
	char file; // col
public:
	Position(string repr); // Throws exception if out of board borders
	~Position();

};
