
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

    void AddGameWall(GameWall wall);

    void AddGameBall(GameBall ball);

    void AddGamePlatform(GamePlatform platform);

    void AddGameBoundary(GameRectangle boundary);

    void SetBackground(GameRectangle background);

    GameRectangle* GetBackground();

private:

    List<GameWall> gameWallList;
    List<GameBall> gameBallList;
    List<GamePlatform> gamePlatformList;
    List<GameRectangle> gameBoundariesList;
    GameRectangle background;

    unsigned int spaceWidth;
    unsigned int spaceHeight;

    unsigned int boundariesDepth;
};
