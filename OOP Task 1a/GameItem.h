#pragma once

#include <assert.h>
#include "constants.h"

using namespace std;

class GameItem
{
public:
#define GAMEITEM       'U'
	// constructors
	GameItem();
	GameItem(int x, int y);

	// assessors
	const int GetX() const;
	const int GetY() const;
	const bool IsAtPosition(int x, int y) const;

	// mutator
	const void setPosition(int x, int y);

protected:
	// data members
	char symbol;
	int x, y;
};
