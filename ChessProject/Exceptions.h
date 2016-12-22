#pragma once

#include <exception>

using namespace std;

class OutOfBorderException : exception
{
public:
	OutOfBorderException();
	//menny was here
	~OutOfBorderException();
};

class UnreachablePositionException : exception
{
public:
	UnreachablePositionException();
	~UnreachablePositionException();
};
