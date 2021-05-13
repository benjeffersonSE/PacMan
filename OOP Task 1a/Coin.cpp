#include "Coin.h"

Coin::Coin() : symbol(COIN)
{
}

Coin::Coin(int x, int y)
{
    symbol = COIN;
    this->x = x;
    this->y = y;
}
