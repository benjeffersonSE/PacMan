#include "raylib.h"
#include "Game.h"
#include <iostream>
#define MAX_INPUT_CHARS     9



int main()
{
    InitWindow(900, 600, "OOP Assignment 1"); // Initialises the window, width and height along with the title OOP Assignment 1
    
    InitAudioDevice(); //Initialises the audio device, used to bring in sounds to the game. Have to use this before loading sounds 
    SetMasterVolume(0.01f); //Sets the volume. 
    Sound* Begin = &LoadSound("pacman_beginning.mp3");//
    Sound* Death = &LoadSound("pacman_death.mp3");// Load sounds that we are using. Using pointers and referencing here as to not create lots of copies of sounds.
    Sound* Munch = &LoadSound("pacman_munch.mp3");//
    Sound* EatGhost = &LoadSound("pacman_eating_ghost.mp3");
    PlaySound(*Begin); //Plays the little opening tune. 

 

     char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for line ending char '\0'
    int letterCount = 0;

    Rectangle textBox = { GetScreenWidth()/4 - 100, 180, 225, 50 };// ?? Just the space for the menu ??
    bool mouseOnText = false;

    int playerSate = 0;
	int ghostState = 0;
    int currentFrame = 0;
	int ghostFrameTime = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    SetTargetFPS(60);

    bool IsGameOver = false; //

	Image clydeImage = LoadImage("sprites32.png");
    Image pinkyImage = LoadImage("sprites32.png");
    Image ghostImage = LoadImage("Redghost.png");         //
    Image pacmanImage = LoadImage("sprites32.png");       //
    Image pelletImage = LoadImage("dots.png");//          Loads images of the sprites 
    Texture2D cherryTexture = LoadTexture("cherry.png");  //
    Image PowerPelletImage = LoadImage("dots.png");       //
    /*Sound EatFruit = LoadSound("pacman_eatfruit");*/

    //Rectangle frameRec = { 0.0f, 0.0f, (float)pacmanImage.width / 11, (float)pacmanImage.height / 13 };
    Rectangle pacmanCrop = Rectangle{ 0, 0, ((float)pacmanImage.width / 11), ((float)pacmanImage.height / 13)};
    ImageCrop(&pacmanImage, pacmanCrop);
    ImageResize(&pacmanImage, 30, 30);

    Rectangle pinkyCrop = Rectangle{ 0, 97, ((float)clydeImage.width / 11), ((float)clydeImage.height / 13) };
    ImageCrop(&pinkyImage, pinkyCrop);
    ImageResize(&pinkyImage, 30, 30);

	Rectangle clydeCrop = Rectangle{ 0, 160, ((float)clydeImage.width / 11), ((float)clydeImage.height / 13) };
	ImageCrop(&clydeImage, clydeCrop);
	ImageResize(&clydeImage, 30, 30);

    Rectangle pelletCrop = Rectangle{0, 0, 16, 16};      //
    ImageCrop(&pelletImage, pelletCrop);                 //These crop the sprites from the sprite sheets.
    ImageResize(&pelletImage, 30, 30);                   //

    Rectangle powerPelletCrop = Rectangle{16, 0, 16, 48};
    ImageCrop(&PowerPelletImage, powerPelletCrop);
    ImageResize(&PowerPelletImage, 30, 30);

    ImageFlipHorizontal(&ghostImage);
	ImageFlipHorizontal(&pacmanImage);

    Rectangle ghostCrop;

    Texture2D pacmanTexture = LoadTextureFromImage(pacmanImage);
	Texture2D clydeTexture = LoadTextureFromImage(clydeImage);
    Texture2D pelletTexture = LoadTextureFromImage(pelletImage);
    Texture2D PowerPelletTexture = LoadTextureFromImage(PowerPelletImage);
    Texture2D ghostTexture = LoadTextureFromImage(ghostImage);
    Texture2D pinkyTexture = LoadTextureFromImage(pinkyImage);
    UnloadImage(pacmanImage);
    UnloadImage(pinkyImage);
    UnloadImage(ghostImage);
    UnloadImage(pelletImage);
    UnloadImage(PowerPelletImage); // THese lines from 64 - 67 unload the images 
                                   // from the memory as they have now been converted
                                   // to textures, using less memory
                                    

    Game game;                     // Instantiates an object of the game class 
    game.Setup();                  // Goes through a level file and adds all the parts of the game to their respective Vectors.
    game.HighScore();              // Searches highscore file for the current hi-score to be displayed             

    while (!WindowShouldClose())
    {
        BeginDrawing();            
        ClearBackground(BLACK);    // Sets background to black
        DrawText("PACMAN", 630, 25, 50, YELLOW); //Writes the word pacman
		DrawText("Level ", 630, 440, 25, YELLOW); //Writes the words 'Level'

		string stringlevel = to_string(game.getLevelNo());
		const char* level = stringlevel.c_str();
		DrawText(level, 710, 440, 25, YELLOW); //Writes the number of the 'Level'


        DrawText("P - Save And Exit", 630, 500, 25, YELLOW); //Writes the words 'p-pause'
        DrawText("E - Exit Game", 630, 530, 25, YELLOW); //Writes the words 'E-Exit Game'
        DrawText("R - Restart Game", 630, 470, 25, YELLOW); //Writes the words 'p-pause'

        string highScore = to_string(game.getHighScore()); //gets highscore from game to be used in the next lines.
        const char* c_highscore = highScore.c_str();
        DrawText("Highscore ", 630, 100, 30, YELLOW);
        DrawText(c_highscore, 800, 100, 30, YELLOW);
        
        string score = to_string(game.getScore());
        const char* c_score = score.c_str();
        DrawText("Score ", 630, 130, 30, YELLOW);
        DrawText(c_score, 800, 130, 30, YELLOW);

        string lives = to_string(game.getLives());
        const char* c_lives = lives.c_str();
        DrawText("Lives ", 630, 160, 30, YELLOW);
        DrawText(c_lives, 800, 160, 30, YELLOW); 
        
        const auto grid = game.PrepareGrid();

		if (game.IsRunning())
		{
			if (IsKeyPressed(KEY_RIGHT))
			{
				game.ChangeDirection(KEY_RIGHT);
                
			}
			if (IsKeyPressed(KEY_LEFT))
			{
				game.ChangeDirection(KEY_LEFT);
                
			}
			if (IsKeyPressed(KEY_UP))
			{
				game.ChangeDirection(KEY_UP);
                
			}
			if (IsKeyPressed(KEY_DOWN))
			{
				game.ChangeDirection(KEY_DOWN);
                
			}
            if (IsKeyPressed(KEY_P))
            {
                ofstream Save("SaveData.txt");
                ofstream SaveScores("SavedScore.txt");
                if (Save.fail())
                {
                    std::cout << "Unable to open saved level file";
                }
                else
                {
					std::cout << "File Opened Correctly";
                    
                    for (int x = 0; x < SIZE; x++)
                    {
                        for (int y = 0; y < SIZE; y++)
                        {
                            switch (grid[x][y])
                            {

                            case FLOOR:		Save << 'f';  break;
                            case WALL:		Save << 'w';  break;
                            case COIN:		Save << 'p';  break;
                            case CLYDE:		Save << 'o';  break;
                            case BLINKY:	Save << 'r';  break;
							case PINKY:		Save << 'i';  break;
                            case PLAYER:	Save << 'v';  break;
                            case POWER:     Save << 'b';  break;
                            case CHERRY:    Save << 'c';  break;

                            default: break;    /* assert(false);*/  // if this hits you probably forgot to add your new tile type :)
                            }
                        }
                        Save << '\n';
                    }
                    Save.close();
                }

                if (SaveScores.fail()) 
				{
					std::cout << "Unable to open saved scores file";
					 
				}
                else 
				{
					std::cout << "File Opened Correctly";
                    SaveScores << game.getScore() << "\n" << game.getLives() << "\n" << game.getLevelNo();
				}
                SaveScores.close();
                return 0;
            }
            if (IsKeyPressed(KEY_E))
            {
                return 0;
            }
            if (IsKeyPressed(KEY_R)) 
			{
				game.ProcessInput(KEY_R);
			}

		}
        else
        {
            //DrawText("TODO: Why did the game end?", 610, 10, 20, LIGHTGRAY);
            if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
            else mouseOnText = false;

            if (mouseOnText)
            {
                // Set the window's cursor to the I-Beam
                // SetMouseCursor(MOUSE_CURSOR_IBEAM);

                // Get char pressed (unicode character) on the queue
                // int key = GetCharPressed();

                // Check if more characters have been pressed on the same frame
                //  while (key > 0)
                {
                    // NOTE: Only allow keys in range [32..125]
                    //   if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                    {
                    //   name[letterCount] = (char)key;
                        letterCount++;
                    }

                  //  key = GetCharPressed();  // Check next character in the queue
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    letterCount--;
                    if (letterCount < 0) letterCount = 0;
                    name[letterCount] = '\0';
                }
            }
           // else if (GetMouseCursor() != MOUSE_CURSOR_DEFAULT) SetMouseCursor(MOUSE_CURSOR_DEFAULT);

            if (mouseOnText) framesCounter++;
            else framesCounter = 0;
        }


        framesCounter++;
        

        if (framesCounter >= (60 / framesSpeed)) // player animation
        {
            framesCounter = 0;
            currentFrame++;
			ghostFrameTime++;

            if (currentFrame > 1.0f)
            {
                playerSate++;
                pacmanImage = LoadImage("sprites32.png");
                
                switch (playerSate)
                {
                case 1:
                    pacmanCrop = Rectangle{ ((float)pacmanImage.width / 10.5f), 0, ((float)pacmanImage.width / 11), ((float)pacmanImage.height / 13) };
                    break;
                case 2:
                    pacmanCrop = Rectangle{ ((float)pacmanImage.width / 5.46f), 0, ((float)pacmanImage.width / 11), ((float)pacmanImage.height / 13) };
                    break;
                case 3:
                    pacmanCrop = Rectangle{ ((float)pacmanImage.width / 10.5f), 0, ((float)pacmanImage.width / 11), ((float)pacmanImage.height / 13) };
                    break;
                case 4:
                    pacmanCrop = Rectangle{ 0, 0, ((float)pacmanImage.width / 11), ((float)pacmanImage.height / 13) };
                    playerSate = 0;
                    break;
                }
                currentFrame = 0;
                ImageCrop(&pacmanImage, pacmanCrop);
                ImageResize(&pacmanImage, 30, 30);
                if (game.playerLookLeft)
                {
                    ImageFlipHorizontal(&pacmanImage);
                }
                if (game.playerLookUp)
                {
                    ImageRotateCCW(&pacmanImage);
                }
                if (game.playerLookDown)
                {
                    ImageRotateCW(&pacmanImage);
                }

                pacmanTexture = LoadTextureFromImage(pacmanImage);
                UnloadImage(pacmanImage);
            }

			if (ghostFrameTime > 5.0f) 
			{
				if (game.isPlayerPoweredUp == true) // *** make a function later that encapsulates isPlayerPowredUp
				{

					ghostImage = LoadImage("sprites32.png");
					ghostCrop = Rectangle{ 0, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
					clydeImage = LoadImage("sprites32.png");
					clydeCrop = Rectangle{ 0, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
                    pinkyImage = LoadImage("sprites32.png");
                    pinkyCrop = Rectangle{ 0, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };

					if (game.powerUpTime <= 5)
					{
						ghostState++;
						switch(ghostState) 
						{
							case 1:
								ghostCrop = Rectangle{ 66, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
								clydeCrop = Rectangle{ 66, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
                                pinkyCrop = Rectangle{ 66, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
								break;
							case 2:
								ghostCrop = Rectangle{ 0, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
								clydeCrop = Rectangle{ 0, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
                                pinkyCrop = Rectangle{ 0, 227, ((float)ghostImage.width / 11), ((float)ghostImage.height / 13) };
								ghostState = 0;
								break;
							default :
								ghostImage = LoadImage("Redghost.png");
								clydeImage = LoadImage("sprites32.png");
                                pinkyImage = LoadImage("sprites32.png");

						}
					}
					if (game.powerUpTime <= 0) 
					{
						game.isPlayerPoweredUp = false;
						game.ghostRunningAway = false;
						ghostImage = LoadImage("Redghost.png");
						clydeImage = LoadImage("sprites32.png");   
						clydeCrop = Rectangle{ 0, 160, ((float)clydeImage.width / 11), ((float)clydeImage.height / 13) };
                        pinkyCrop = Rectangle{ 0, 97, ((float)clydeImage.width / 11), ((float)clydeImage.height / 13) };

					}

					ImageCrop(&ghostImage, ghostCrop);
					ImageResize(&ghostImage, 30, 30);
                    ImageCrop(&clydeImage, clydeCrop);
                    ImageResize(&clydeImage, 30, 30);
                    ImageCrop(&pinkyImage, pinkyCrop);
                    ImageResize(&pinkyImage, 30, 30);
					ghostTexture = LoadTextureFromImage(ghostImage);
					clydeTexture = LoadTextureFromImage(clydeImage);
                    pinkyTexture = LoadTextureFromImage(pinkyImage);
					UnloadImage(ghostImage);
                    UnloadImage(clydeImage);
                    UnloadImage(pinkyImage);
					ghostFrameTime = 0;
				}
			}

            //frameRec.x = (float)currentFrame * (float)pacmanImage.width / 11;
        }

        const int cellSize = (int)((float)GetScreenHeight() / (float)(SIZE));
        
        


        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                int xPosition = x * cellSize;
                int yPosition = y * cellSize;

                switch (grid[y][x])
                {
                case FLOOR:  DrawRectangle(xPosition, yPosition, cellSize, cellSize, BLACK);  break;
                case WALL:   DrawRectangle(xPosition, yPosition, cellSize, cellSize, VIOLET); break;
				case GAMEITEM: 
					DrawTexture(pelletTexture, xPosition, yPosition, RAYWHITE);
					break;
                case COIN:
                    DrawTexture(pelletTexture, xPosition, yPosition, RAYWHITE);
                    //DrawRectangle(xPosition, yPosition, cellSize, cellSize, GOLD);   
                    break;
                case GHOST:
                    DrawTexture(ghostTexture, xPosition, yPosition, RAYWHITE);
                    //DrawRectangle(xPosition, yPosition, cellSize, cellSize, RED);    
                    break;
                case CLYDE:
                    DrawTexture(clydeTexture, xPosition, yPosition, RAYWHITE);
                    break;
				case BLINKY:
					DrawTexture(ghostTexture, xPosition, yPosition, RAYWHITE);
					break;
                case PINKY:
                    DrawTexture(pinkyTexture, xPosition, yPosition, RAYWHITE);
                    break;
                case PLAYER:
                    DrawTexture(pacmanTexture, xPosition, yPosition, RAYWHITE);
                    //DrawRectangle(xPosition, yPosition, cellSize, cellSize, YELLOW); 
                    break;
                case POWER:
                    DrawTexture(PowerPelletTexture, xPosition, yPosition, RAYWHITE); 
					break;
                case CHERRY:  
					DrawTexture(cherryTexture, xPosition, yPosition, RAYWHITE); 
					break;

                default:     assert(false);  // if this hits you probably forgot to add your new tile type :)
                }

                // draw lines around each tile, remove this if you don't like it!
                DrawRectangleLines(x * cellSize, y * cellSize, cellSize, cellSize, BLACK);
            }
            
        }
		if (game.HasPlayerBeatGame)
		{
			DrawText("Congrats you", 625, 200, 30, YELLOW);
            DrawText("beat the game!", 625, 240, 30, YELLOW);

		}

        if (game.HasPlayerWon() && game.getLevelNo() < 3)
        {
            DrawText("Player Has Won ", 630, 200, 30, YELLOW);
            //player.UpdatePosition(PositionInMiddleOfGrid());
            
            DrawText("Continue: ", 630, 300, 25, YELLOW);
            int iCounter = game.getRestartCounter();
            string restartCounter = to_string(iCounter);
            const char* c_restart = restartCounter.c_str();
			DrawText(c_restart, 800, 300, 30, YELLOW);

        }
		if (game.restart) 
		{
			DrawText("Restarting: ", 630, 300, 25, YELLOW);
			int iCounter = game.getRestartCounter();
			string restartCounter = to_string(iCounter);
			const char* c_restart = restartCounter.c_str();
			DrawText(c_restart, 800, 300, 30, YELLOW);
		}
        if (game.PlayMunchSound)
        {
			if (!IsSoundPlaying(*Munch)) {
				PlaySound(*Munch);
				game.PlayMunchSound = false;
			}
        }
        if (game.PlayDeathSound)
        {
            PlaySound(*Death);
            game.PlayDeathSound = false;
        }
        if (game.PlayEatGhostSound)
        {
            PlaySound(*EatGhost);
            game.PlayEatGhostSound = false;
        }
		if(game.needToResume) 
		{
			DrawText("Ready: ", 630, 300, 30, YELLOW);
			int iCounter = game.getRestartCounter();
			string restartCounter = to_string(iCounter);
			const char* c_restart = restartCounter.c_str();


			DrawText(c_restart, 800, 300, 30, YELLOW);
		}
        if(game.PlayerLostALife()) 
        {
            DrawText("Ready: ", 630, 300, 30, YELLOW);           
            int iCounter = game.getRestartCounter();
            string restartCounter = to_string(iCounter);
            const char* c_restart = restartCounter.c_str();
            
            
            DrawText(c_restart, 800, 300, 30, YELLOW);
        }

		float time = GetFrameTime();
        
		game.Update(time);

        EndDrawing();

        
    }
   
    UnloadTexture(ghostTexture);
    UnloadTexture(pacmanTexture);
    UnloadTexture(pelletTexture);
	UnloadTexture(ghostTexture);
	UnloadTexture(clydeTexture);
    UnloadTexture(pinkyTexture);
	UnloadTexture(cherryTexture);
    UnloadSound(*Begin);
    UnloadSound(*Death);// Unload sound data
    UnloadSound(*Munch);
       // Unload sound data
    CloseAudioDevice();     // Close audio device
    CloseWindow();
    return 0;
}



