
#pragma once

#include "GameObject.h"
#include "ArkanoidList.hpp"

class Level
{

public:

    /*
    @brief
    Default constructor
    */
    Level();

    /*
    @brief
    Constructor of a generic level with a starting game platform and a starting game ball
    @param spaceWidth: the width (in pixels) of the space for the walls
    @param spaceHeight: the height (in pixels) of the space for the walls
    @param boundariesDepth: the space (in pixels) of the boundaries walls from the edges
    */
    Level(unsigned int spaceWidth, unsigned int spaceHeight, unsigned int boundariesDepth);

    /*
    @brief
    Add a game wall to the list of game walls of the level
    @param wall: the pointer to the game wall to add
    */
    void AddGameWall(GameWall* wall);

    /*
    @brief
    Add a game ball to the list of game balla of the level
    @param ball: the pointer to the game ball to add
    */
    void AddGameBall(GameBall* ball);

    /*
    @brief
    Add a game platform to the list of game platforms of the level
    @param platform: the pointer to the game platform to add
    */
    void AddGamePlatform(GamePlatform* platform);

    /*
    @brief
    Add a game boundary to the list of game boundaries of the level
    @param boundary: the pointer to the game boundary to add
    */
    void AddGameBoundary(GameRect* boundary);

    /*
    @brief
    Level background setter
    @param wall: the pointer to the game rect which is the background
    */
    void SetBackground(GameRect* background);

    /*
    @brief
    Level background getter
    */
    GameRect* GetBackground();

    ~Level();

private:

    List<GameWall*> gameWallList;
    List<GameBall*> gameBallList;
    List<GamePlatform*> gamePlatformList;
    List<GameRect*> gameBoundariesList;
    GameRect* background;

    unsigned int spaceWidth;
    unsigned int spaceHeight;

    unsigned int boundariesDepth;
};
