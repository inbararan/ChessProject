#pragma once

#include <exception>

using namespace std;

// Position::Position throws if row/col out of borders
class OutOfBorderException : exception
{
public:
	OutOfBorderException();
	~OutOfBorderException();
};

// Unit::pathToMove throws if dest unrachable
class UnreachablePositionException : exception
{
public:
	UnreachablePositionException();
	~UnreachablePositionException();
};
