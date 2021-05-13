#pragma once

#include <assert.h>
#include "constants.h"
#include "Ghost.h"

using namespace std;

class Pinky : public Ghost
{

public:
#define PINKY       'I'
	// constructors
	Pinky();

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