#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;
///
/// Setup and Game initialisation.g
/// 

//This function loads in the level designs from files and initialises variables to values that they need to be at the beginning of a game or after a win.
void Game::Setup()
{
    //Set up the variables needed to run the game, this happens on start up and after every time you die in the game or have completed a level.
    HasPlayerLostALife = false;
    HasClydeMoved = true;
    HasBlinkyMoved = true;
    HasPinkyMoved = true;
	needToResume = false;
    ghostExitSpawn = false;
    ghostRunningAway = false;
	isSavedFileEmpty = false;
	isUsingSavedData = false;
	const char* Dir = "";

    //Sets up a stream of all the level designs so that we can use them all later during the game.
	ifstream saveFile("SaveData.txt");
	ifstream scoreFile("LoadScore.txt");
    ifstream savedScore("SavedScore.txt");

	if (saveFile.peek() == std::ifstream::traits_type::eof())
	{
		// Empty File
		isSavedFileEmpty = true;
	}
	if (!(saveFile.peek() == std::ifstream::traits_type::eof()))
	{
		isSavedFileEmpty = false;
	}

	if (isSavedFileEmpty)
	{
        switch(getLevelNo())
        {
        case 1:
            Dir = "Level1.txt";
			setLevelNo(1);
            break;
        case 2:
            Dir = "Level2.txt";
			setLevelNo(2);
            break;
        case 3:
            Dir = "Level3.txt";
			setLevelNo(3);
            break;
        default:
            Dir = "Level1.txt";
			setLevelNo(1);
            break;
        }
		isUsingSavedData = false;
		//file.open("Level1.txt");
	}

	if (!isSavedFileEmpty)
	{
		Dir = "SaveData.txt";
		needToResume = true;
		ghostExitSpawn = true;
		HasClydeMoved = false;
		HasBlinkyMoved = false;
		HasPinkyMoved = false;
		isUsingSavedData = true;
		//file.open("SaveData.txt");
	}

	ifstream file(Dir);

	//ifstream file (Dir);        
	//ifstream file (ifstream(Dir));                             //Opens an input stream and reads in the text file 'level1.txt' to generate the level.



    //LineNum is used to parse through each line of the level file.
    int lineNum = 0;

    //Te switch case takes in the level number which is increased after you beat a level, and it starts at one for the initial load of the game. ***Not yet working, unsure why***
    
	if (file.fail())
	{             // Checks if file exists/in the right place, if not game doesn't hard crash and lets us know whats wrong.
		cout << "\nAn error has occurred when opening the file.";
	}
	else
	{
		cout << "File opened correctly";
		string str = "";              // Variable that holds a line of the text file, to be parsed through to pull in the level design.
		int lineNum = 0;
		while (getline(file, str))
		{ // Until the loop hits the bottom of the file/reads the last line
			for (int i = 0; i < 20; i++) // Parses each line of the file going character to character. 
			{
				switch (str[i])  // str[i] is depending on what i is a character that we define below in the switch to create our grid.
				{
				case 'w':
					walls.push_back(Wall(i + 1, lineNum + 1));
					break;
				case 'g':
					ghosts.push_back(Ghost(i + 1, lineNum + 1));
					break;
				case 'b':
					PowerPellets.push_back(PowerPellet(i + 1, lineNum + 1));
					break;
				case 'c':
					Cherries.push_back(Cherry(i + 1, lineNum + 1));
					break;
				case 'p':
					coins.push_back(Coin(i + 1, lineNum + 1));
					break;
				case 'r':
					blinky.setPosition(i + 1, lineNum + 1);
					break;
				case 'o':
					clyde.setPosition(i + 1, lineNum + 1);
					break;
				case 'i':
					pinky.setPosition(i + 1, lineNum + 1);
                    break;
				case 'v':
					player.setPosition(i + 1, lineNum + 1);
				default:
					break;
				}

			}
			lineNum += 1;     // This is how we tell the program where the Y variable of the object is.
			


			//lineNum += 1;     // This is how we tell the program where the Y variable of the object is.

		}
		file.close();             // Closes the file, to help with memory.
        ofstream FileToEmpty;
        FileToEmpty.open("SaveData.txt", ofstream::out | ofstream::trunc);  // Wipes the savedata file so that if you then exit again, when you load the game it starts over.
        FileToEmpty.close();                                                // Closes the file.
	}
	if(savedScore.fail())
	{
		cout << "\nAn error has occurred when opening the file.";
	}
    else 
	{
		string str = "";              // Variable that holds a line of the text file, to be parsed through to pull in the Saved score and saved level.
		int lineNum = 1;
        int score = 0;
		while (getline(savedScore, str)) //While we aren't at the end of the file. Pull in the next line of the file.
		{
            score = stoi(str);           //Converts the str to an int.
			switch(lineNum)              //Depending if it is the first or second line of the file we need to pull in either score or lives that are saved from the last game.
			{
				case 1:
                    setScore(score);     //Set the players score to what it was when they saved the game.
                    break;
                case 2:
                    setLives(score);     //Set the players Lives to what it was when they saved the game.
                    break;
				case 3:
					setLevelNo(score);   //Set the level number to what it was when the player saved the game.					   
					break;
                default:
                    setScore(0);         //If there is nothing in the SaveScores/Lives file we still need to set the data so here the default is 0 score and 3 lives.
                    setLives(3);
					setLevelNo(1);
                    break;
			}
            lineNum++;                   //Increases linenumber which is how we use our switch case.
		}
        savedScore.close();              //Close the stream.
        ofstream FileToEmpty;
        FileToEmpty.open("SavedScore.txt", ofstream::out | ofstream::trunc); // Wipes the savedata file so that if you then exit again, when you load the game it starts over.
        FileToEmpty.close();                                                 //Closes the File.
	}

	if (player.getLives() == 3)
	{
		needToResume = true;
	}

	coinOriginalSize = coins.size(); // get list of coins for each setup
}


void Game::LoadGhosts() 
{
    clyde.setPosition(8, 12);
    pinky.setPosition(10, 12);
    blinky.setPosition(12, 12);
}

void Game::Clear()
{
    walls.clear();
    coins.clear();
    PowerPellets.clear();
}

///
/// Player Functions
/// 

//Checks if the player can turn, and if so it changes the way the player is facing.
const void Game::ChangeDirection(int key)
{
    bool canChangeDirection = false; 
    switch (key)
    {
    case KEY_RIGHT:
        for (int i = 0; i < walls.size(); i++)
        {
            //This if/else statement fixes the bug where the player could turn and stop if there was a wall next to them.
            if (walls[i].GetX() == (player.GetX() + 1) && walls[i].GetY() == player.GetY() || ((player.GetX() + 1 > 20)))//if there is a wall to the right of the player
            {
                // do not change direction
                canChangeDirection = false;
                return;
            }
            else
            {
                canChangeDirection = true;
            }
        }
        break;
    case KEY_LEFT:
        for (int i = 0; i < walls.size(); i++)
        {
            //This if/else statement fixes the bug where the player could turn and stop if there was a wall next to them.
            if (walls[i].GetX() == (player.GetX() - 1) && walls[i].GetY() == player.GetY() || ((player.GetX() - 1 < 1)))//if there is a wall to the left of the player
            {
                // do not change direction
                canChangeDirection = false;
                return;
            }
            else
            {
                canChangeDirection = true;
            }
        }
        break;
    case KEY_UP:
        for (int i = 0; i < walls.size(); i++)
        {
            //This if/else statement fixes the bug where the player could turn and stop if there was a wall next to them.
            if (walls[i].GetY() == (player.GetY() - 1) && walls[i].GetX() == player.GetX() || ((player.GetY() - 1 < 1)))//if there is a wall to the top of the player
            {
                // do not change direction
                canChangeDirection = false;
                return;
            }
            else
            {
                canChangeDirection = true;
            }
        }
        break;
    case KEY_DOWN:
        for (int i = 0; i < walls.size(); i++)
        {
            //This if/else statement fixes the bug where the player could turn and stop if there was a wall next to them.
            if ((walls[i].GetY() == (player.GetY() + 1) && walls[i].GetX() == player.GetX()) || ((player.GetY() + 1 > 20)))//if there is a wall or edge of screen to the bottom of the player
            {
                // do not change direction
                canChangeDirection = false;
                return;
            }
            else
            {
                canChangeDirection = true;
            }
        }
        break;
    default:

        break;

    }
    if (canChangeDirection) //THis if here checks if the player can change direction before they do change direction, it works with the switch case above to fix the bug where the player could change direction and stop next to a wall.
    {
        currentDirection = key;

        switch (currentDirection)
        {
        case KEY_RIGHT:
            playerLookLeft = false; // These bools are here to alter which way the player is looking when they turn.
            playerLookRight = true; //Player faces right.
            playerLookUp = false;
            playerLookDown = false;
            break;
        case KEY_LEFT:
            playerLookLeft = true; // These bools are here to alter which way the player is looking when they turn.
            playerLookRight = false; //Player faces left.
            playerLookUp = false;
            playerLookDown = false;
            break;
        case KEY_UP:
            playerLookLeft = false; // These bools are here to alter which way the player is looking when they turn.
            playerLookRight = false; //Player faces up.
            playerLookUp = true;
            playerLookDown = false;
            break;
        case KEY_DOWN:
            playerLookLeft = false; // These bools are here to alter which way the player is looking when they turn.
            playerLookRight = false;// Player faces down.
            playerLookUp = false;
            playerLookDown = true;
            break;

        }
    }
}

//Moves the player around the grid and stops them if they are to hit a wall.
const void Game::ProcessInput(int key)
{
    //This switch case calls the move function in the player class, that moves the player around the grid.
	switch(key)
	{
	case KEY_R:
		restart = true;
		break;
	case 0:
		currentDirection = 0;
		break;
	default:
		break;
	}

    switch (currentDirection)
    {
    case KEY_RIGHT:
        player.Move(key);          
        break;
    case KEY_LEFT:
        player.Move(key);
        break;
    case KEY_UP:
        player.Move(key);
        break;
    case KEY_DOWN:
        player.Move(key);
        break;
    }

    //This statement checks if the player is going to hit a wall, and stops them from moving if they are going to hit a wall. The player can then choose where they would like to turn.
    if (IsPlayerAtWall(player.GetX(), player.GetY())) 
    {
        switch (currentDirection)
        {
        case 262: // rightKey
            ProcessInput(263); // Move player back - leftKey
            break;
        case 263: // leftkey
            ProcessInput(262); // Move player back - rightKey
            break;
        case 264: // downKey
            ProcessInput(265); // Move player back - upKey
            break;
        case 265: // upKey
            ProcessInput(264); // Move player back - downkey
            break;
        }
        currentDirection = 0;
        ProcessInput(currentDirection);
        playerInput = 0.2f;
    }
}

/// 
/// Player Collision Checks with other entities such as Coins, Power Pellets and ghosts.
/// 

 //Checks if player is at coin.
const bool Game::IsPlayerAtCoin(int x, int y) const
{
    for (size_t i = 0; i < coins.size(); i++)
    {
        if (coins[i].IsAtPosition(x, y) == player.IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

// Checks if player is at ghost.
const bool Game::IsPlayerAtGhost(int x, int y) const
{
    for (size_t i = 0; i < ghosts.size(); i++)
    {
        if (ghosts[i].IsAtPosition(x, y) == player.IsAtPosition(x, y))
        {
            return true;
        }
    }
    return false;
}

//Checks if player is at Ornge ghost.
const bool Game::IsPlayerAtClyde(int x, int y) const
{
    if (clyde.IsAtPosition(x, y) == player.IsAtPosition(x, y))
    {
		//PlayDeathSound = true; // play death sound
        return true;
    }
    return false;
}

//Checks if player is at red ghost.
const bool Game::IsPlayerAtBlinky(int x, int y) const
{
    if (blinky.IsAtPosition(x, y) == player.IsAtPosition(x, y))
    {
        //PlayDeathSound = true; // play death sound
        return true;
    }
    return false;
}

//Checks if player is at the pink ghost.
const bool Game::IsPlayerAtPinky(int x, int y) const
{
    if (pinky.IsAtPosition(x, y) == player.IsAtPosition(x, y))
    {
        //PlayDeathSound = true; // play death sound
        return true;
    }
    return false;
}

//Checks if player is at PowerPellet.
const bool Game::IsPlayerAtPowerPellet(int x, int y) const // Checks if player is at powerpellet
{
    for (size_t i = 0; i < PowerPellets.size(); i++)
    {
        if (PowerPellets[i].IsAtPosition(x, y) == player.IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

// CHecks if player is at cherry
const bool Game::IsPlayerAtCherry(int x, int y) const
{
    for (size_t i = 0; i < Cherries.size(); i++)
    {
        if (Cherries[i].IsAtPosition(x, y) == player.IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

/// 
///Ghost Functions - Includes all 4 ghosts.
/// 

///
/// Ghost Movement.
/// 

//Moves clyde 
const void Game::MoveClyde(int direction)
{
	clydeInput = direction;
    if (clydeInput == 0) 
    {
        clydeInput = clyde.getDirection();
    }
    switch (clydeInput)
    {
    case 262:
        clyde.Move(262);
        break;
    case 263:
        clyde.Move(263);
        break;
    case 264:
        clyde.Move(264);
        break;
    case 265:
        clyde.Move(265);
        break;
    }
    //Adds collision with walls.
    if (IsClydeAtWall(clyde.GetX(), clyde.GetY())) 
    {
        switch (clydeInput)
        {
        case 262: // right
            clydeInput = 263;
            MoveClyde(clydeInput); // Move clyde back.
			clydeInput = 1;
            break;
        case 263: // left
			clydeInput = 262;
            MoveClyde(clydeInput);
			clydeInput = 1;
            break;
        case 264: // down
			clydeInput = 265;
            MoveClyde(clydeInput);
			clydeInput = 1;
            break;
        case 265: // up
			clydeInput = 264;
            MoveClyde(clydeInput);
			clydeInput = 1;
            break;
        }
        //direction = 0;
        //HasClydeMoved = false;
        MoveClyde(clydeInput);
    }
}

//Moves pinky
const void Game::MovePinky(int direction)
{
	pinkyInput = direction;
	if (pinkyInput == 0)
	{
		pinkyInput = pinky.getDirection();
	}
	switch (pinkyInput)
	{
	case 262:
		pinky.Move(262);
		break;
	case 263:
		pinky.Move(263);
		break;
	case 264:
		pinky.Move(264);
		break;
	case 265:
		pinky.Move(265);
		break;
	}

	if (IsPinkyAtWall(pinky.GetX(), pinky.GetY()))
	{
		switch (pinkyInput)
		{
		case 262: // rightKey
			pinkyInput = 263;
			MovePinky(pinkyInput); // Move player back - leftKey
			pinkyInput = 1;
			break;
		case 263: // leftkey
			// Move player back - rightKey
			pinkyInput = 262;
			MovePinky(pinkyInput);
			pinkyInput = 1;
			break;
		case 264: // downKey
			pinkyInput = 265;
			MovePinky(pinkyInput);
			pinkyInput = 1;
			// Move player back - upKey
			break;
		case 265: // upKey
			pinkyInput = 264;
			MovePinky(pinkyInput);
			pinkyInput = 1;
			// Move player back - downkey
			break;
		}
		//direction = 0;
		//HasClydeMoved = false;
		//HasPinkyMoved = false;
		MovePinky(pinkyInput);
	}
}

// Moves blinky around the grid.
const void Game::MoveBlinky(int direction)
{
	blinkyInput = direction;
	switch (blinkyInput)
	{
	case 262:
		blinky.Move(262);
		break;
	case 263:
		blinky.Move(263);
		break;
	case 264:
		blinky.Move(264);
		break;
	case 265:
		blinky.Move(265);
		break;
	}

	if (IsBlinkyAtWall(blinky.GetX(), blinky.GetY()))
	{
		switch (blinkyInput)
		{
		case 262: // rightKey
			blinkyInput = 263;
			MoveBlinky(blinkyInput); // Move player back - leftKey
			blinkyInput = 1;
			break;
		case 263: // leftkey
			// Move player back - rightKey
			blinkyInput = 262;
			MoveBlinky(blinkyInput);
			blinkyInput = 1;
			break;
		case 264: // downKey
			blinkyInput = 265;
			MoveBlinky(blinkyInput);
			blinkyInput = 1;
			// Move player back - upKey
			break;
		case 265: // upKey
			blinkyInput = 264;
			MoveBlinky(blinkyInput);
			blinkyInput = 1;
			// Move player back - downkey
			break;
		}
		//direction = 0;
		//HasClydeMoved = false;
		//HasBlinkyMoved = false;
		MoveBlinky(blinkyInput);
	}
}

///
/// Ghost location checks.
/// 

//This goes through the ghosts vector and returns true or falls when given a coordinate parameter asking if a cherry is at that coordinate.
const bool Game::IsGhostAtPosition(int x, int y) const
{
    for (size_t i = 0; i < ghosts.size(); ++i)
    {
        if (ghosts[i].IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}



//Checks if the orange ghost has exited spawn.
const bool Game::HasClydeExitSpawn(int x, int y) const
{
    if (clyde.IsAtPosition(x, y) < (10, 10))
    {
        return true;
    }

    return false;
}

//Checks if the red ghost has exited spawn.
const bool Game::HasBlinkyExitSpawn(int x, int y) const
{
    if (blinky.IsAtPosition(x, y) < (10, 10))
    {
        return true;
    }

    return false;
}

//Checks if the pink ghost has exited spawn.
const bool Game::HasPinkyExitSpawn(int x, int y) const
{
    if (pinky.IsAtPosition(x, y) < (10, 10))
    {
        return true;
    }

    return false;
}

/// <summary>
/// This function builds up a 2D grid of characters representing the current state of the game.
/// The characters are later used to decide which colour sqaure to display, but you could display images instead.
/// </summary>
vector<vector<char>> Game::PrepareGrid()
{

    // create the 2D grid
    vector<vector<char>> grid;

    // for each row
    for (int row = 1; row <= SIZE; ++row)
    {
        // create the inner vector to add to the 2D grid
        vector<char> line;

        // for each column, work out what's in that position and add the relevant char to the 2D grid
        for (int col = 1; col <= SIZE; ++col)
        {
            if (row == player.GetY() && col == player.GetX())
            {
                line.push_back(PLAYER);
            }
			else if (IsCherryAtPosition(col, row))//loads first to make sure that a coin is not loaded before it and then the cherry is skipped
            {
                line.push_back(CHERRY);
            }
			else if (IsGhostAtPosition(col, row))
			{
				line.push_back(GHOST);
			}
			else if (row == blinky.GetY() && col == blinky.GetX()) 
            {
                line.push_back(BLINKY);
            }
            else if (row == clyde.GetY() && col == clyde.GetX()) 
            {
                line.push_back(CLYDE);
            }
            else if (row == pinky.GetY() && col == pinky.GetX())
            {
                line.push_back(PINKY);
            }
            else if (IsWallAtPosition(col, row))
            {
                line.push_back(WALL);
            }
            else if (IsPowerPelletAtPosition(col, row))
            {
                line.push_back(POWER);
            }
            else if (IsCoinAtPosition(col, row)) 
            {
                line.push_back(COIN);
            }
            else
            {
                line.push_back(FLOOR);
            }
        }

        // now that the row is full, add it to the 2D grid
        grid.push_back(line);
    }

    return grid;
}

///
/// Vector Functions. i.e. Coins, Walls Cherries.
/// 
//This goes through the walls vector and returns true or falls when given a coordinate parameter asking if a wall is at that coordinate
const bool Game::IsWallAtPosition(int x, int y) const
{
    for (size_t i = 0; i < walls.size(); i++)
    {
        if (walls[i].IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

//This goes through the coins vector and returns true or falls when given a coordinate parameter asking if a coin is at that coordinate
const bool Game::IsCoinAtPosition(int x, int y) const
{
    for (size_t i = 0; i < coins.size(); i++)
    {
        if (coins[i].IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

//This goes through the cherries vector and returns true or falls when given a coordinate parameter asking if a cherry is at that coordinate
const bool Game::IsCherryAtPosition(int x, int y) const
{
    for (size_t i = 0; i < Cherries.size(); i++)
    {
        if (Cherries[i].IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

//This goes through the PowerPellet vector and returns true or falls when given a coordinate parameter asking if a PowerPellet is at that coordinate.
const bool Game::IsPowerPelletAtPosition(int x, int y) const
{
    for (size_t i = 0; i < PowerPellets.size(); i++)
    {
        if (PowerPellets[i].IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

///
/// Collision Checks for each entity with walls on the grid.
/// 

// Checks if the player is at the wall.
const bool Game::IsPlayerAtWall(int x, int y) const 
{
    for(size_t i = 0; i < walls.size(); i++) 
    {
        if (walls[i].IsAtPosition(x, y) == player.IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

//Checks if the orange ghost is at the wall.
const bool Game::IsClydeAtWall(int x, int y) const
{
    for (size_t i = 0; i < walls.size(); i++) 
    {
        if (walls[i].IsAtPosition(x, y) == clyde.IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}

//Checks if the red ghost is at the wall.
const bool Game::IsBlinkyAtWall(int x, int y) const
{
	for (size_t i = 0; i < walls.size(); i++)
	{
		if (walls[i].IsAtPosition(x, y) == blinky.IsAtPosition(x, y))
		{
			return true;
		}
	}

	return false;
}

//Checks if the pink ghost is at the wall.
const bool Game::IsPinkyAtWall(int x, int y) const
{
    for (size_t i = 0; i < walls.size(); i++)
    {
        if (walls[i].IsAtPosition(x, y) == pinky.IsAtPosition(x, y))
        {
            return true;
        }
    }

    return false;
}


/// 
/// Functions to run the game.
/// 

// Checks if the game is still running, checks if the player has lost a life or if theyve won to determine what happens next to the game.
const bool Game::IsRunning()
{
	if(restart) 
	{
		return false;
	}
	if(needToResume)
	{
		return false;
	}
    if(HasPlayerWon()) 
    {
        ProcessInput(0);
        return false;
    }
    if (!PlayerLostALife())
    {
        return true;
    }
    if (getLives() == 0)
    {
        ProcessInput(0);
        return false;
    }
    
    ProcessInput(0);
    return false;
}

const void Game::LoadCherry()
{
	int nx = (rand() % 20) + 1; // random x, between 1 and 20.
	int ny = (rand() % 20) + 1; // random y, between 1 and 20. The Size of the grid(20x20).

	bool positionAvailable = false; // bool we'll use for checking if the random position we have created for the cherry is available.

    
    while(!positionAvailable) // loop while we have not found a correct position (we don't want cherry spawning on a wall!)
	{
        if(!IsWallAtPosition(nx, ny) && IsCoinAtPosition(nx, ny) && !IsPowerPelletAtPosition(nx,ny) ) // checks the position to place a cherry is not a wall or power pellet and is a coin
		{
			Cherries.push_back(Cherry(nx, ny));// create new cherry with random position and push onto vector
            positionAvailable = true;// set the position as available so while loop will end
			cherrySpawned = true;//set true so another cherry cannot be spawned
		}
		else 
        {
			nx = (rand() % 20) + 1; // make a new random if the current random we have selected is unavailable (Occupied by a wall or a power pellet.)
			ny = (rand() % 20) + 1; // Same as above.
	
        }
    }
}

//Checks if the player has lost a life. 
const bool Game::PlayerLostALife() const //Checks mov
{
    if(HasPlayerLostALife) 
    {
        return true;
    }

    return false;
}

// Checks if the player has won the game, called from 'IsRunning'
const bool Game::HasPlayerWon() const
{
   if (coins.size() <= 0) //If there are no coins left on the grid.
   {
       return true; //Player has won.
   }
   return false;    //Player has not won.
}

//Returns the players score.
const int Game::getScore() const
{
    return player.getScore();
}

//Returns the players highscore.
const int Game::getHighScore() const
{
    return player.getHighScore();
}

//Sets the players score.
const void Game::setScore(int score)
{
    this->score = score;
    player.setScore(score);
}

//Sets the players highscore.
const void Game::setHighScore(int highScore) 
{
    this->highScore = highScore;
    player.setHighScore(highScore);
}

//Sets the players lives, so we can give more or less later once we determine the games difficulty.
const void Game::setLives(int lives) 
{
    player.setLives(lives);
}

//Returns the amount of lives a player has.
const int Game::getLives() const
{
    return player.getLives();
}

const int Game::getLevelNo() const
{
	return levelNo;
}

const void Game::setLevelNo(int levelNo) 
{
	this->levelNo = levelNo;
}

const void Game::increaseLevelNo(int levelNo) 
{
	this->levelNo += levelNo;
}

//Sets the amount of time on the restart counter.
const void Game::setRestartCounter(float restartCounter) 
{
    this->restartCounter = restartCounter;
}

//Return the amount of time on the counter.
const float Game::getRestartCounter() 
{
    return restartCounter;
}

///
/// THe function that handles all the game events
/// 

const void Game::Update(float time)
{
    countDown -= time;                       // Makes the countdown work by reducing it by one every tick.
    playerInput -= time;                     // If player presses a button the game knows that and the output of the button press happens this tick.
    ghostCountDown -= time;                 
    ghostMoveFromSpawnCounter -= time;
    ghostSpawnMovementSpeed -= time;
    ///
    /// Ghost Movement on update
    /// 

    // Here we check if the ghosts have waited in spawn long enough. We can edit the amount of time in game.h
    if (ghostMoveFromSpawnCounter <= 0)
    {
        //Checks if the ghosts have made it out of the spawn point.
        if (!ghostExitSpawn)
        {
            //If they haven't yet made it out of the spawn then they are made to move out of spawn.
            ghostMoveFromSpawnCounter = 0;

            //This if statement gives the ghosts a different movement speed to what they have when moving out of spawn.
            if (ghostSpawnMovementSpeed <= 0)
            {
                ghostSpawnMovementSpeed = 0.5f;
                
                ///
                ///Blinky the red ghost movement.
                ///

                //Function to move blinky the red ghost. Movement is different depending on if the player is powered up. If the player is powered up then the ghost will run away which is tackled later on.
                if (HasBlinkyMoved && !isPlayerPoweredUp)
                {
                    blinky.Move(265);

                    if (blinky.GetX() < 10)
                    {
                        blinkyInput = 262;
                        MoveBlinky(blinkyInput);
                    }
                    if (blinky.GetX() > 10)
                    {
                        blinkyInput = 263;
                        MoveBlinky(blinkyInput);
                    }
                    if (blinky.GetY() < 10)
                    {
                        blinkyInput = 265;
                        MoveBlinky(blinkyInput);
                    }
                    if (blinky.GetX() == 10 && blinky.GetY() == 10)
                    {
                        HasBlinkyMoved = false; //This line checks if the ghost is out of the spawn box yet. So that they can move out of there before we start trying to move them around the grid.
                    }
                }

                ///
                /// Pinky the pink ghost movement.
                ///

                //Statement to move pinky the pink ghost. Movement is different depending on if the player is powered up. If the player is powered up then the ghost will run away which is tackled later on.
                if (HasPinkyMoved && !isPlayerPoweredUp)
                {
                    pinky.Move(265);

                    if (pinky.GetX() < 10)
                    {
                        pinkyInput = 262;
                        MovePinky(pinkyInput);
                    }
                    if (pinky.GetX() > 10)
                    {
                        pinkyInput = 263;
                        MovePinky(pinkyInput);
                    }
                    if (pinky.GetY() < 10)
                    {
                        pinkyInput = 265;
                        MovePinky(pinkyInput);
                    }
                    if (pinky.GetX() == 10 && pinky.GetY() == 10)
                    {
                        HasPinkyMoved = false; //This line checks if the ghost is out of the spawn box yet. So that they can move out of there before we start trying to move them around the grid.
                    }
                }

                ///
                /// Clyde the orange ghost movement.
                ///

                //Function to move Clyde the orange ghost. Movement is different depending on if the player is powered up. If the player is powered up then the ghost will run away which is tackled later on.
                if (HasClydeMoved && !isPlayerPoweredUp)
                {
                    clyde.Move(265);

                    if (clyde.GetX() < 10)
                    {
                        clydeInput = 262;
                        MoveClyde(clydeInput);
                    }
                    if (clyde.GetX() > 10)
                    {
                        clydeInput = 263;
                        MoveClyde(clydeInput);
                    }
                    if (clyde.GetY() > 10)
                    {
                        clydeInput = 265;
                        MoveClyde(clydeInput);
                    }
                    if (clyde.GetX() == 10 && clyde.GetY() == 10)
                    {
                        HasClydeMoved = false; //This line checks if the ghost is out of the spawn box yet. So that they can move out of there before we start trying to move them around the grid.
                    }
                }

                //This tells the program that on the next run through of the update function, the ghosts are out of the spawn box and we can begin moving them around the grid.
                if ((clyde.GetX() == 10 && clyde.GetY() == 10) && (blinky.GetX() == 10 && blinky.GetY() == 10) && (pinky.GetX() == 10 && pinky.GetY() == 10))
                {
                    ghostExitSpawn = true;
                    HasBlinkyMoved = false;
                    HasClydeMoved = false;
					HasPinkyMoved = false;
                }
            }
        }
    }

    ///
    /// Moving on from ghost movement.
    ///

    if(!cherrySpawned && (coins.size() < (coinOriginalSize /  4))) // if there is only 1/4 of the coins left we spawn a cherry!
	{
		LoadCherry(); // Runs the function to push a cherry at a random position on the grid.
    }
    
    if (isPlayerPoweredUp)
    {
        ghostRunningAway = true;
        powerUpTime -= time;
    }


    //Countdown is how we run the game at every 0.2 ticks.
    if (countDown <= 0) // loops every 0.2 seconds
    {
        ProcessInput(currentDirection);
        countDown = 0.2f;
    }

    ///
    /// More ghost movement.
    ///


    if (ghostCountDown <= 0) // loops every 0.3 seconds
    {

		if (!HasClydeMoved)
		{
			if ((clyde.GetX() == 10 && clyde.GetY() == 10) || (clyde.GetX() == 10 && clyde.GetY() == 9))
			{
				clydeInput = 265;
				MoveClyde(clydeInput);
			}
			if (clydeInput == 1)
			{
				clydeInput = 0;
			}
			MoveClyde(clydeInput);
		}

		if (!HasPinkyMoved)
		{
			if ((pinky.GetX() == 10 && pinky.GetY() == 10) || (pinky.GetX() == 10 && pinky.GetY() == 9))
			{
				pinkyInput = 265;
				MovePinky(pinkyInput);
			}
			if (pinkyInput == 1)
			{
				pinkyInput = 0;
			}
			MovePinky(pinkyInput);
		}

        if (!HasBlinkyMoved)
        {
            if ((blinky.GetX() == 10 && blinky.GetY() == 9) || (blinky.GetX() == 10 && blinky.GetY() == 10))
            {
                blinkyInput = 265;
                MoveBlinky(blinkyInput);
            }
            if (!ghostRunningAway)
            {
                if (blinky.GetX() < player.GetX())
                {
                    blinkyInput = 262;
                    MoveBlinky(blinkyInput);
                }
                if (blinky.GetX() > player.GetX())
                {
                    blinkyInput = 263;
                    MoveBlinky(blinkyInput);
                }
                if (blinky.GetY() < player.GetY())
                {
                    blinkyInput = 264;
                    MoveBlinky(blinkyInput);
                }
                if (blinky.GetY() > player.GetY())
                {
                    blinkyInput = 265;
                    MoveBlinky(blinkyInput);
                }
            }
            if (ghostRunningAway)
            {

                if (blinky.GetX() > player.GetX())
                {
                    blinkyInput = 262;
                    MoveBlinky(blinkyInput);
                }
                if (blinky.GetX() < player.GetX())
                {
                    blinkyInput = 263;
                    MoveBlinky(blinkyInput);
                }
                if (blinky.GetY() > player.GetY())
                {
                    blinkyInput = 264;
                    MoveBlinky(blinkyInput);
                }
                if (blinky.GetY() < player.GetY())
                {
                    blinkyInput = 265;
                    MoveBlinky(blinkyInput);
                }
            }

            //MoveBlinky(blinkyInput);
        }
        ghostCountDown = 0.3f;
    }

    if(!IsRunning())  // if the game is no longer running (player has finished the game)
    {
        restartCounter -= time; // counts down from 5
		if (!needToResume) // we only want to reload ghosts if we don't need to resume
		{
			if(!restart) 
			{
				LoadGhosts();
			}
		}
		HasClydeMoved = true;
		HasBlinkyMoved = true;
        HasPinkyMoved = true;
		ghostExitSpawn = false;
		ghostMoveFromSpawnCounter = 3.0f; // wait 3 seconds to release ghost
		ghostSpawnMovementSpeed = 0.5f;

		if(getLevelNo() >= 3 && HasPlayerWon())
		{
			// player has won the whole game
			// do something here
			countDown = 0;
			restartCounter = 0;
			playerInput = 0;
			ghostCountDown = 0;
			ghostMoveFromSpawnCounter = 0;
			ghostSpawnMovementSpeed = 0;
			endOfGame();
			HasPlayerBeatGame = true;
			return;
		}

		if (PlayerLostALife())
		{
			player.setPosition(10, 18); // resets player position
		}

		if(restart) 
		{
			ProcessInput(0); // player will not move
		}

		if(needToResume) 
		{
			ProcessInput(0); // player will not move
		}

        if(restartCounter <= 0) // after 5 seconds
        {
            restartCounter = 5.0f;

			if(restart) 
			{
				player.setPosition(10, 18); // resets player position
				Restart();
				restart = false;
			}

			if(needToResume) 
			{
				if(isUsingSavedData) // only if were resuming from loading a save do we want to ghosts not to move out of the box
				{
					ghostExitSpawn = true;
					HasClydeMoved = false;
					HasBlinkyMoved = false;
					HasPinkyMoved = false;
				}
				else 
				{
					ghostExitSpawn = false;
					HasClydeMoved = true;
					HasBlinkyMoved = true;
					HasPinkyMoved = true;
				}
				needToResume = false;
			}

            //player.UpdatePosition(270, 270);
            if (HasPlayerWon()) 
            {              
				increaseLevelNo(1);
                cherrySpawned = false;
				Clear();
				PrepareGrid();
				Setup();
				LoadGhosts();
				HighScore();
            }
            if (PlayerLostALife()) 
            {
                //ghosts.push_back(Ghost(10, 10));
                PrepareGrid();
                HasPlayerLostALife = false;
            }
            if (getLives() <= 0)
            {
				endOfGame();
				Restart();
            }
        }

    }

	if (IsPlayerAtCherry(player.GetX(), player.GetY()))
	{
		player.increaseScore(200);
		for (int i = 0; i < Cherries.size(); i++)
		{
			if (Cherries[i].GetX() == player.GetX() && Cherries[i].GetY() == player.GetY())
			{
				Cherries.erase(Cherries.begin() + i);
				break;
			}
		}
	}

    if (IsPlayerAtCoin(player.GetX(), player.GetY()))
    {
		PlayMunchSound = true;
        player.increaseScore(1);
        for (int i = 0; i < coins.size(); i++)
        {
            if (coins[i].GetX() == player.GetX() && coins[i].GetY() == player.GetY())
            {
                coins.erase(coins.begin() + i);
                break;
            }
        }
    }
    if (IsPlayerAtGhost(player.GetX(), player.GetY()))
    {
        player.decreaseLives(1);
        for (int i = 0; i < ghosts.size(); i++)
        {
            if (ghosts[i].GetX() == player.GetX() && ghosts[i].GetY() == player.GetY())
            {
                HasPlayerLostALife = true;
                ghosts.erase(ghosts.begin() + i);
                break;
            }
        }
    }

    if(IsPlayerAtClyde(player.GetX(), player.GetY())) 
    {
        if (clyde.GetX() == player.GetX() && clyde.GetY() == player.GetY()) 
        {
			clydeInput = 1;
			clyde.Move(clydeInput);

			if (!ghostRunningAway) 
			{
				player.decreaseLives(1);
                PlayDeathSound = true; // play death sound
				HasPlayerLostALife = true;
			}
			else if(ghostRunningAway) 
			{
				clyde.setPosition(8, 12);
				HasClydeMoved = true;
				ghostExitSpawn = false;
                PlayEatGhostSound = true;
				ghostMoveFromSpawnCounter = 3.0f; // wait 3 seconds to release ghost
				ghostSpawnMovementSpeed = 0.5f;
                player.increaseScore(200);
			}
        }
    }

	if (IsPlayerAtBlinky(player.GetX(), player.GetY()))
	{
		if (blinky.GetX() == player.GetX() && blinky.GetY() == player.GetY())
		{
			blinkyInput = 0;
			blinky.Move(blinkyInput);

			if (!ghostRunningAway)
			{
				player.decreaseLives(1);
                PlayDeathSound = true; // play death 
				HasPlayerLostALife = true;
			}
			else if (ghostRunningAway)
			{
				blinky.setPosition(12, 12);
				HasBlinkyMoved = true;
				ghostExitSpawn = false;
                PlayEatGhostSound = true;
				ghostMoveFromSpawnCounter = 3.0f; // wait 3 seconds to release ghost
				ghostSpawnMovementSpeed = 0.5f;
                player.increaseScore(200);
			}
		}
	}

    if (IsPlayerAtPinky(player.GetX(), player.GetY()))
    {
        if (pinky.GetX() == player.GetX() && pinky.GetY() == player.GetY())
        {
            pinkyInput = 0;
            pinky.Move(pinkyInput);

            if (!ghostRunningAway)
            {
                player.decreaseLives(1);
                PlayDeathSound = true; // play death 
                HasPlayerLostALife = true;
            }
			else if (ghostRunningAway)
            {
				pinky.setPosition(10, 12);
                HasPinkyMoved = true;
                ghostExitSpawn = false;
                PlayEatGhostSound = true;
                ghostMoveFromSpawnCounter = 3.0f; // wait 3 seconds to release ghost
                ghostSpawnMovementSpeed = 0.5f;
                player.increaseScore(200);
            }
        }
    }

    if (IsPlayerAtPowerPellet(player.GetX(), player.GetY()))
    {
        player.increaseScore(50);
        for (int i = 0; i < PowerPellets.size(); i++)
        {
            if (PowerPellets[i].GetX() == player.GetX() && PowerPellets[i].GetY() == player.GetY())
            {
                isPlayerPoweredUp = true;
				powerUpTime = 0.00f; // reset counter
                powerUpTime += 10.0f; // make counter 10 seconds
                PowerPellets.erase(PowerPellets.begin() + i);
                break;
            }
        }
        return;
    }
	if (player.GetX() == 10 && player.GetY() == 10) // stop player getting into spawn box
	{
		playerInput = 265;
		player.Move(playerInput);
	}

    ///
    /// Teleportaion around the grid when necessarary.
    ///
    
    //Level 1 Teleports
	if (player.GetX() == 1 && player.GetY() == 10 && countDown > 0.2 && getLevelNo() == 1) // if player is in the left tube of the screen
    {
        player.setPosition(20, 10); // change position
    }
    else if (player.GetX() == 20 && player.GetY() == 10 && countDown > 0.2 && getLevelNo() == 1) // if player is in the right tube of the screen
    {
        player.setPosition(1, 10); // change position
    }

    //Level 2 Teleports
    if (player.GetX() == 3 && player.GetY() == 20 && countDown > 0.2 && getLevelNo() == 2) // if player is in the left tube of the screen
    {
        player.setPosition(17, 20); // change position
		ChangeDirection(265);
    }
    else if (player.GetX() == 17 && player.GetY() == 20 && countDown > 0.2 && getLevelNo() == 2) // if player is in the right tube of the screen
    {
        player.setPosition(3, 20); // change position
		ChangeDirection(265);
    }

    //Level 3 teleports
    if (player.GetX() == 6 && player.GetY() == 20 && countDown > 0.2 && getLevelNo() == 3) // if player is in the left tube of the screen
    {
        player.setPosition(6, 1); // change position
		ChangeDirection(264); //Change to which ever is down.
    }
    else if (player.GetX() == 6 && player.GetY() == 1 && countDown > 0.2 && getLevelNo() == 3) // if player is in the right tube of the screen
    {
        player.setPosition(6, 20); // change position
		ChangeDirection(265); // Change to which ever is up.
    }
    else if (player.GetX() == 14 && player.GetY() == 1 && countDown > 0.2 && getLevelNo() == 3) // if player is in the right tube of the screen
    {
        player.setPosition(14, 20); // change position
		ChangeDirection(265); // Change to which ever is up.
    }
    else if (player.GetX() == 14 && player.GetY() == 20 && countDown > 0.2 && getLevelNo() == 3) // if player is in the right tube of the screen
    {
        player.setPosition(14, 1); // change position
		ChangeDirection(264); // Change to which ever is down.
    }

    ///
    ///Ghosts at the edge of the screen.
    ///


    if ((clyde.GetX() == 1 || clyde.GetY() == 1 || clyde.GetX() == 20 || clyde.GetY() == 20) && countDown > 0.2) // if ghost has hit the edge of the screen
    {
        clydeInput = 0; // new random position
    }

	if ((pinky.GetX() == 1 || pinky.GetY() == 1 || pinky.GetX() == 20 || pinky.GetY() == 20) && countDown > 0.2) // if ghost has hit the edge of the screen
	{
		pinkyInput = 0; // new random position
	}
}

    ///
    /// End of game functions.
    ///

const void Game::endOfGame()
{
    ofstream HighScores;
    HighScores.open("highScores.txt", std::ios_base::app); // append to highscores document
    HighScores << player.getScore() << endl; // add player's new score
    HighScores.close(); // new score
}

//Loads and sorts highscores in the highscore file to be displayed.
void Game::HighScore() 
{
    ifstream highscoreFile("highScores.txt");

    if (highscoreFile.fail())       // Checks if file exists/in the right place, if not game doesn't hard crash and lets us know whats wrong.
    {
        cout << "\nAn error has occurred when opening the file.\n";
    }
    else
    {
        cout << "\nFile opened correctly.\n";
        string str = "";            // Creates a variable 'str' with an empty string. 'str' is used to store the next line of the file. 
        while (getline(highscoreFile, str)) //Until we reach the end of the file. 
        {
            int n = stoi(str);      // Converts our string that we got from the file into an integer we are calling 'n'
            int max = 0;            //Bigger score
            int min = 0;            
            int i = 0;
            while (highscoreFile >> n)
            {
                if (!n) break;
                if (i++ == 0)
                {
                    min = n;
                    max = n;
                }                   //Very Basic bubble sort algorithm. -W
                if (n < min)
                {
                    min = n;
                }
                else if (n > max)
                {
                    max = n;
                }
                setHighScore(max);
            }
        }
    }

    highscoreFile.close();         //Closes the highscore file 

}

void Game::Restart() 
{
	setLevelNo(1); // if you die you want to go back to level 1
	Clear();
    cherrySpawned = false;
	ghostMoveFromSpawnCounter = 3.0f; // wait 3 seconds to release ghost
	ghostSpawnMovementSpeed = 0.5f;
	LoadGhosts();
	PrepareGrid();
	Setup();
	setScore(0);
	setLives(3);
	HighScore();
}

