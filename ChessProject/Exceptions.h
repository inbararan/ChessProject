#pragma once

#include <exception>

using namespace std;

class OutOfBorderException : exception
{
public:
	OutOfBorderException();
	~OutOfBorderException();
};

class UnreachablePositionException : exception
{
public:
	UnreachablePositionException();
	~UnreachablePositionException();
};
