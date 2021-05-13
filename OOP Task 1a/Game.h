#pragma once

#include <assert.h>	
#include <string>		
#include <vector>
#include "Player.h"
#include "Clyde.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Wall.h"
#include "Ghost.h"
#include "GameItem.h"
#include "Coin.h"
#include "PowerPellet.h"
#include "Cherry.h"
#include <fstream>

using namespace std;

class Game
{
   public:
      // initialise variables
      Player player;
      Blinky blinky;
      Clyde clyde;
      Pinky pinky;
      Cherry cherry;
      vector<vector<char>> PrepareGrid();

	  // variables and counters
	  int currentDirection = 0;
	  int clydeInput = 0;
	  int blinkyInput = 0;
      int pinkyInput = 0;
	  int coinOriginalSize = 0; // used to check when only 1/4 of coins are left

	  float ghostCountDown = 0.3f;
	  float ghostMoveFromSpawnCounter = 3.0f; // wait 3 seconds to release ghost
	  float ghostSpawnMovementSpeed = 0.5f;
      float powerUpTime = 0.0f;
	  float countDown = 0.2f;
      float animationTime = 0.2f;
      float playerInput = 0.2f;
      float restartCounter = 5.0f; // one second (we'll count down from 5)
      
	  // bools used for checks

	  // time related
	  bool restart = false;
	  bool needToResume = false;

	  // file related
	  bool isSavedFileEmpty = false;
	  bool isUsingSavedData = false;

	  // sound checks
      bool PlayDeathSound = false;
      bool PlayMunchSound = false;
      bool PlayEatGhostSound = false;
	  // object creation check
	  bool cherrySpawned = false;

	  // checking ghost bools
	  bool ghostRunningAway = false;
	  bool ghostRespawn = false;
	  bool ghostExitSpawn = false;

	  // movement bools
	  bool HasClydeMoved = false;
	  bool HasBlinkyMoved = false;
	  bool HasPinkyMoved = false;

	  // These bools, are all used to return which way pacman is looking as to switch the direction of the sprite.
      bool playerLookLeft = false;	
      bool playerLookRight = false;	
      bool playerLookUp = false;	
      bool playerLookDown = false;

	  // win or lose checks
      bool HasPlayerLostALife = false;
	  bool HasPlayerBeatGame = false;
      bool isPlayerPoweredUp = false;

      // Objects contained in game

	  // accessors

		  const float getRestartCounter();
		  const int getHighScore() const;
		  const int getScore() const;
		  const int getLives() const;
		  const int getLevelNo() const;

		  const bool IsRunning();
		  const bool IsWallAtPosition(int x, int y) const;
		  const bool IsCoinAtPosition(int x, int y) const;
		  const bool IsPowerPelletAtPosition(int x, int y) const;
		  const bool IsCherryAtPosition(int x, int y) const;
		  const bool IsGhostAtPosition(int x, int y) const;

		  // Player functions 
		  const bool IsPlayerAtWall(int x, int y) const;
		  const bool IsPlayerAtClyde(int x, int y) const;
		  const bool IsPlayerAtBlinky(int x, int y) const;
		  const bool IsPlayerAtPinky(int x, int y) const;
		  const bool IsPlayerAtCoin(int x, int y) const;
		  const bool IsPlayerAtGhost(int x, int y) const;
		  const bool IsPlayerAtPowerPellet(int x, int y) const;
		  const bool IsPlayerAtCherry(int x, int y) const;

		  const bool HasPlayerWon() const;
		  const bool PlayerLostALife() const;

		  // ghost
		  const bool IsClydeAtWall(int x, int y) const;
		  const bool IsBlinkyAtWall(int x, int y) const;
		  const bool IsPinkyAtWall(int x, int y) const;

		  const bool HasClydeExitSpawn(int x, int y) const;
		  const bool HasBlinkyExitSpawn(int x, int y) const;
		  const bool HasPinkyExitSpawn(int x, int y) const;


	  // mutators

		  const void setHighScore(int highScore);
		  const void setRestartCounter(float restartCounter);
		  const void setLives(int lives);
		  const void setScore(int score);
		  const void setLevelNo(int levelNo);
		  const void increaseLevelNo(int levelNo);

		  //Functions used start of the game
		  void Setup();
		  void Restart();
		  void LoadGhosts();
		  void HighScore();
		  void Clear();

		  // used during the duration of the game
		  const void Update(float time);
		  const void LoadCherry();
		  const void endOfGame();
      
		  //Movement functions
		  const void ProcessInput(int key);
		  const void ChangeDirection(int key);

		  // Ghost functions
		  const void MovePinky(int directon);
		  const void MoveClyde(int direction);
		  const void MoveBlinky(int direction);

   private:  

       //Variables 
       int score = 0;
       int highScore = 0;
       int levelNo = 1; // track which level number were on
       

       //Vectors
       vector<Wall> walls;
       vector<Coin> coins;
       vector<Ghost> ghosts;
       vector<PowerPellet> PowerPellets;
       vector<Cherry> Cherries;
       
       

};