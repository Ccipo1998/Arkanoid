
#include "Level.h"
#include "ArkanoidPhysics.h"

Level::Level()
    : background(nullptr)
    , levelStarted(false)
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

void Level::SetWallsSpace(GameRect* wallsSpace)
{
    this->wallsSpace = wallsSpace;
}

GameRect* Level::GetWallsSpace()
{
    return this->wallsSpace;
}

void Level::SetPlatformSpace(GameRect* platformSpace)
{
    this->platformSpace = platformSpace;
}

GameRect* Level::GetPlatformSpace()
{
    return this->platformSpace;
}

void Level::HandleEvents(SDL_Event& sdlEvent)
{
    // platform events
    for (unsigned int i = 0; i < this->gamePlatformList.GetSize(); ++i)
        this->gamePlatformList[i]->HandleEvent(sdlEvent);

    // ball event
    if (sdlEvent.type == SDL_MOUSEBUTTONDOWN && !this->levelStarted)
    {
        // launch the game ball
        if (this->gameBallList.GetSize() > 0)
        {
            this->gameBallList[0]->Launch();

            this->levelStarted = true;
        }
    }
}

void Level::Update(double deltaTime)
{
    // call updates of balls and walls

    // if level is not started, the ball needs to move with the platform
    if (!this->levelStarted && this->gameBallList.GetSize() > 0 && this->gamePlatformList.GetSize() > 0)
        this->gameBallList[0]->position.x = this->gamePlatformList[0]->position.x + this->gamePlatformList[0]->width / 2.0f - this->gameBallList[0]->width / 2.0f;

    // game balls
    for (unsigned int i = 0; i < this->gameBallList.GetSize(); ++i)
        this->gameBallList[i]->Update(deltaTime);

    // game walls
    for (unsigned int i = 0; i < this->gameWallList.GetSize(); ++i)
        this->gameWallList[i]->Update(deltaTime);

    // collision detection and response

    // game walls
    for (unsigned int i = 0; i < this->gameWallList.GetSize(); ++i)
    {
        // only if enabled
        if (!this->gameWallList[i]->IsEnabled())
            continue;

        if (phys::collisionCheck(*this->gameWallList[i], *this->gameBallList[0]))
            phys::collisionResponse(*this->gameWallList[i], *this->gameBallList[0], deltaTime);
    }

    // game boundaries
    for (unsigned int i = 0; i < this->gameBoundaryList.GetSize(); ++i)
    {
        // only if enabled
        if (!this->gameBoundaryList[i]->IsEnabled())
            continue;

        if (phys::collisionCheck(*this->gameBoundaryList[i], *this->gameBallList[0]))
            phys::collisionResponse(*this->gameBoundaryList[i], *this->gameBallList[0], deltaTime);
    }

    // game platforms
    for (unsigned int i = 0; i < this->gamePlatformList.GetSize(); ++i)
    {
        // only if enabled
        if (!this->gamePlatformList[i]->IsEnabled())
            continue;

        if (phys::collisionCheck(*this->gamePlatformList[i], *this->gameBallList[0]))
            phys::collisionResponse(*this->gamePlatformList[i], *this->gameBallList[0], deltaTime);
    }
}

void Level::Render()
{
    // render background
    if (this->background != nullptr)
        this->background->Render();

    // render boundaries
    #ifdef BUILD_DEBUG
        for (unsigned int i = 0; i < this->gameBoundaryList.GetSize(); ++i)
            this->gameBoundaryList[i]->Render();
    #endif

    // render walls
    for (unsigned int i = 0; i < this->gameWallList.GetSize(); ++i)
    {
        this->gameWallList[i]->Render();
    }

    // render platforms
    for (unsigned int i = 0; i < this->gamePlatformList.GetSize(); ++i)
    {
        this->gamePlatformList[i]->Render();
    }

    // render balls
    for (unsigned int i = 0; i < this->gameBallList.GetSize(); ++i)
    {
        this->gameBallList[i]->Render();
    }
}

Level::~Level()
{
    // the lists free their memory and the memory of the object contained by themselves

    delete this->background;
    delete this->wallsSpace;
    delete this->platformSpace;
}
