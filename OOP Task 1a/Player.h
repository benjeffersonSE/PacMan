#pragma once

#include "constants.h"

class Player
{
    public:
        // constructor
        Player();

        //Definition
        #define PLAYER    'V'
        
        // assessors
        const bool IsAtPosition(int x, int y) const;
        const int GetX() const;
        const int GetY() const;
        const int getScore() const;
        const int getHighScore() const;
        const int getLives() const;

        // mutators
        const void Move(int key);
        const void setScore(int score);
        const void setHighScore(int highScore);
        const void increaseScore(int score);
        const void setLives(int lives);
        const void decreaseLives(int lives);
        const void setPosition(int ix, int iy);

    private:
        // data members
        char symbol;
        int  x, y;
        int dx;
        int dy;
        int score = 0;
        int highScore = 0;
        int lives = 3;
        // supporting functions 
		const void UpdatePosition(int dx, int dy);
        
};