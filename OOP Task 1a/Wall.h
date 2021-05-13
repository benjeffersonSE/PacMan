#pragma once

#include <assert.h>
#include "constants.h"

using namespace std;

class Wall
{
    public:
        #define WALL        'W'
        // constructors
        Wall();
        Wall(int x, int y);

        // assessors
        const int GetX() const;
        const int GetY() const;
        const bool IsAtPosition(int x, int y) const;

    private:
        // data members
        char symbol;
        int x, y;
};