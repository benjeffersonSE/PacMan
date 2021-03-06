#pragma once

#include <assert.h>
#include "constants.h"
#include "Ghost.h"

using namespace std;

class Blinky : public Ghost
{

public:
#define BLINKY       'R'
	// constructors
	Blinky();
	Blinky(int x, int y);

	string getGhostName() const override;

private:
	// data members
	int x, y;
	char symbol;
	int dx;
	int dy;
	int direction = 0;
	// support functions
};