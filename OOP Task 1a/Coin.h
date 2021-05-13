#pragma once

#include <assert.h>
#include "constants.h"
#include "GameItem.h"

using namespace std;

class Coin: public GameItem
{
public:
#define COIN       'P'
    // constructors
    Coin();
	Coin(int x, int y);

    // assessors

private:
    // data members
    char symbol;
};