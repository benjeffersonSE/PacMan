#pragma once

#include <assert.h>
#include "constants.h"
#include "GameItem.h"

using namespace std;

class Cherry: public GameItem
{
public:
#define CHERRY       'C'
    // constructors
    Cherry();
    Cherry(int x, int y);

private:
    // data members
    char symbol;
};