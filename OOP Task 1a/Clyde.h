#pragma once

#include <assert.h>
#include <stdlib.h>
#include "constants.h"
#include "Ghost.h"

using namespace std;

class Clyde: public Ghost
{

public:
#define CLYDE       'O'
    // constructors
    Clyde();
    Clyde(int x, int y);

    // assessors
    string getGhostName() const override;
    // mutators

private:
    // data members
    int x, y;
    char symbol;
    int dx;
    int dy;
    int direction = 0;
    // support functions
};
