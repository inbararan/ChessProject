#pragma once

#include <exception>

using namespace std;

// Position::Position throws if row or col out of borders
class OutOfBoardException : exception
{
public:
	OutOfBoardException();
	~OutOfBoardException();
};

// Unit::pathToMove throws if dest unrachable
class UnreachablePositionException : exception
{
public:
	UnreachablePositionException();
	~UnreachablePositionException();
};
