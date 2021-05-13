#include "PowerPellet.h"


PowerPellet::PowerPellet() : symbol(POWER)
{
}

PowerPellet::PowerPellet(int x, int y)
{
    symbol = POWER;
    this->x = x;
    this->y = y;
}