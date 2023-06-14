
#include "Level.h"

Level::Level() {}

Level::Level(unsigned int spaceWidth, unsigned int spaceHeight, unsigned int boundariesDepth)
    : spaceWidth(spaceWidth)
    , spaceHeight(spaceHeight)
    , boundariesDepth(boundariesDepth)
    {}

void Level::AddGameWall(GameWall wall)
{
    this->gameWallList.Add(wall);
}

void Level::AddGameBall(GameBall ball)
{
    this->gameBallList.Add(ball);
}

void Level::AddGamePlatform(GamePlatform platform)
{
    this->gamePlatformList.Add(platform);
}

void Level::AddGameBoundary(GameRectangle boundary)
{
    this->gameBoundariesList.Add(boundary);
}

void Level::SetBackground(GameRectangle background)
{
    this->background = background;
}

GameRectangle* Level::GetBackground()
{
    return &this->background;
}
