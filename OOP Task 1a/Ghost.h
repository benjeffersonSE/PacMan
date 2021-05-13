#pragma once

#include <assert.h>
#include <stdlib.h>
#include "constants.h"

using namespace std;

class Ghost
{
public:
#define GHOST       'G'
	// constructors
	Ghost();
	Ghost(int x, int y);

	// assessors
	const int GetX() const;
	const int GetY() const;
	const int getDirection() const;
	const bool IsAtPosition(int x, int y) const;

	// mutators
	const void Move(int direction);
	const void setPosition(int x, int y);

protected:
	// data members
	int x, y;
	char symbol;
	int dx;
	int dy;
	int direction = 0;
	// support functions
	const void UpdatePosition(int dx, int dy);
};