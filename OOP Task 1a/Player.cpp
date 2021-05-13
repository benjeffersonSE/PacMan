#include "Player.h"

Player::Player() : symbol(PLAYER), x(0), y(0), dx(0), dy(0)
{
}

const int Player::GetX() const // Players X coordinate
{
    return x;
}

const int Player::GetY() const // Players Y coordinate
{
    return y;
}


const int Player::getScore() const // Returns player score
{
    return score;
}

const int Player::getHighScore() const
{
    return highScore;
}

const int Player::getLives() const // Gets player lives
{
    return lives;
}

const bool Player::IsAtPosition(int x, int y) const // Checks where the player is on the grid
{
    return this->x == x && this->y == y;
}

const void Player::setPosition(int ix, int iy) // Sets player position
{
    x = ix;
    y = iy;
}

const void Player::Move(int key) // Moves the player depending on input
{
    switch (key)
    {
    case KEY_LEFT:
        dx = -1;
        dy = 0;
        break;
    case KEY_RIGHT:
        dx = +1;
        dy = 0;
        break;
    case KEY_UP:
        dx = 0;
        dy = -1;
        break;
    case KEY_DOWN:
        dx = 0;
        dy = +1;
        break;
    default:
        // not a key we care about, so do nothing
        break;
    }

    // update mouse coordinates if move is possible
    if (((x + dx) >= 1) && ((x + dx) <= SIZE) && ((y + dy) >= 1) && ((y + dy) <= SIZE))
    {
        UpdatePosition(dx, dy);
    }
}

const void Player::UpdatePosition(int dx, int dy) // Updates the players position on the grid
{
    x += dx;
    y += dy;
}

const void Player::setScore(int score) // Sets player score 
{
    this->score = score;
}

const void Player::setHighScore(int highScore) // Sets high score
{
    this->highScore = highScore;
}

const void Player::increaseScore(int score) // Increase score by 1
{
    this->score += score;
}

const void Player::setLives(int lives) // Sets the lives of the player 
{
    this->lives = lives;
}

const void Player::decreaseLives(int lives) // decreases lives by one
{
    this->lives -= lives;
}
