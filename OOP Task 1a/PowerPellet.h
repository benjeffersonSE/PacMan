#pragma once

#include <assert.h>
#include "constants.h"
#include "GameItem.h"

using namespace std;

class PowerPellet: public GameItem
{
public:
#define POWER       'B'
    // constructors
    PowerPellet();
    PowerPellet(int x, int y);

private:
    // data members
    char symbol;
};
