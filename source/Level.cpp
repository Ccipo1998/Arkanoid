
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
    this->gameBoundaryList.Add(boundary);
}

void Level::SetBackground(GameRect* background)
{
    this->background = background;
}

GameRect* Level::GetBackground()
{
    return this->background;
}

unsigned int Level::GetBoundariesDepth()
{
    return this->boundariesDepth;
}

unsigned int Level::GetSpaceWidth()
{
    return this->spaceWidth;
}

unsigned int Level::GetSpaceHeight()
{
    return this->spaceHeight;
}

void Level::Render()
{
    // render background
    if (this->background != nullptr && this->background->IsEnabled())
        this->background->Render();

    // render boundaries
    #ifdef BUILD_DEBUG
        for (unsigned int i = 0; i < this->gameBoundaryList.GetSize(); ++i)
        {
            if (this->gameBoundaryList[i]->IsEnabled())
                this->gameBoundaryList[i]->Render();
        }
    #endif

    // render walls
    for (unsigned int i = 0; i < this->gameWallList.GetSize(); ++i)
    {
        if (this->gameWallList[i]->IsEnabled())
            this->gameWallList[i]->Render();
    }

    // render platforms
    for (unsigned int i = 0; i < this->gamePlatformList.GetSize(); ++i)
    {
        if (this->gamePlatformList[i]->IsEnabled())
            this->gamePlatformList[i]->Render();
    }

    // render balls
    for (unsigned int i = 0; i < this->gameBallList.GetSize(); ++i)
    {
        if (this->gameBallList[i]->IsEnabled())
            this->gameBallList[i]->Render();
    }
}

Level::~Level()
{
    // the lists free their memory and the memory of the object contained by themselves

    delete this->background;
}
