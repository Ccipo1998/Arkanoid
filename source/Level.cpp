
#include "Level.h"

Level::Level()
    : background(nullptr)
    {}

Level::Level(unsigned int spaceWidth, unsigned int spaceHeight, unsigned int boundariesDepth)
    : spaceWidth(spaceWidth)
    , spaceHeight(spaceHeight)
    , boundariesDepth(boundariesDepth)
    , background(nullptr)
    {}

void Level::AddGameWall(GameWall* wall)
{
    this->gameWallList.Add(wall);
}

void Level::AddGameBall(GameBall* ball)
{
    this->gameBallList.Add(ball);
}

void Level::AddGamePlatform(GamePlatform* platform)
{
    this->gamePlatformList.Add(platform);
}

void Level::AddGameBoundary(GameRect* boundary)
{
    this->gameBoundariesList.Add(boundary);
}

void Level::SetBackground(GameRect* background)
{
    this->background = background;
}

GameRect* Level::GetBackground()
{
    return this->background;
}

Level::~Level()
{
    // the lists free their memory and the memory of the object contained by themselves

    delete this->background;
}
