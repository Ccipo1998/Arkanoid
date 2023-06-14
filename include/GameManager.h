
// TODO store texture, manage levels, game space and other things...

#pragma once

// Design choice: to be used as a singleton

#include "SDL_mixer.h"
#include "SDL_image.h"

#include <string>
#include "ArkanoidList.hpp"
#include "Level.h"

class GameManager
{

public:

    /*
    @brief
    Constructor of the arkanoid game manager
    */
    GameManager();

    /*
    @brief
    SDL library initialization
    @param windowWidth: the width of the game window (in pixels)
    @param windowHeight: the height of the game window (in pixels)
    */
    bool InitializeSDL(unsigned int windowWidth, unsigned int windowHeight);

    /*
    @brief
    SDL library closing
    */
    void CloseSDL();

    /*
    @brief
    Loading and initialization of the assets for the game
    */
    void LoadPrefabs();

    /*
    @brief
    Generate a randomic level taking assets from the prefabs
    */
    void GenerateRandomLevel();

    /*
    @brief
    Getter for the current level
    */
    Level* GetCurrentLevel();

    unsigned int windowWidth;
    unsigned int windowHeight;

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Mix_Music* music;

private:

    List<GameWallPrefab> WallPrefabs;
    List<GameRectanglePrefab> BackgroundsPrefabs;
    List<GameRectanglePrefab> PlatformPrefabs;
    GameBallPrefab BallPrefab;

    unsigned int score;

    Level currentLevel;

};
