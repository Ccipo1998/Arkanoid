
#include "Level.h"
#include "ArkanoidPhysics.h"
#include "GameManager.h"
#include "Singleton.hpp"

Level::Level()
    : background(nullptr)
    , levelStarted(false)
    , status(LevelStatus::RUNNING)
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

LevelStatus Level::GetLevelStatus()
{
    return this->status;
}

void Level::HandleEvents(SDL_Event& sdlEvent)
{
    // platform events
    for (unsigned int i = 0; i < this->gamePlatformList.GetSize(); ++i)
        this->gamePlatformList[i]->HandleEvent(sdlEvent);

    // ball event
    if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        #ifdef BUILD_DEBUG
            // launch the game ball many times
            if (this->gameBallList.GetSize() > 0)
            {
                this->gameBallList[0]->position = vec2f(this->gamePlatformList[0]->position.x + this->gamePlatformList[0]->width / 2.0f - this->gameBallList[0]->width / 2.0f, this->gamePlatformList[0]->position.y - this->gameBallList[0]->height);
                this->gameBallList[0]->Launch();

                this->levelStarted = true;
            }
        #else
            // launch the game ball
            if (this->gameBallList.GetSize() > 0 && !this->levelStarted)
            {
                this->gameBallList[0]->Launch();

                this->levelStarted = true;
            }
        #endif
    }
}

void Level::Update(double deltaTime)
{
    unsigned int remainingWalls = this->gameWallList.GetSize();
    unsigned int remainingBalls = this->gameBallList.GetSize();

    // call updates of platform, balls and walls

    for (unsigned int i = 0; i < this->gamePlatformList.GetSize(); ++i)
    {
        if (!this->gamePlatformList[i]->IsEnabled())
            continue;

        this->gamePlatformList[i]->Update(deltaTime);
    }

    // game balls
    for (unsigned int i = 0; i < this->gameBallList.GetSize(); ++i)
    {
        if (!this->gameBallList[i]->IsEnabled())
        {
            // update remaining number
            --remainingBalls;
            
            continue;
        }

        // check if the ball is lost
        GameManager* manager = Singleton<GameManager>::GetInstance();
        if (this->gameBallList[i]->position.y > manager->windowHeight)
            this->gameBallList[i]->Disable();

        this->gameBallList[i]->Update(deltaTime);
    }

    // game walls
    for (unsigned int i = 0; i < this->gameWallList.GetSize(); ++i)
    {
        if (!this->gameWallList[i]->IsEnabled())
            continue;

        this->gameWallList[i]->Update(deltaTime);
    }

    // collision detection and response (target = platform)

    for (unsigned int i = 0; i < this->gameBoundaryList.GetSize(); ++i)
    {
        if (aphys::collisionCheck(*this->gameBoundaryList[i], *this->gamePlatformList[0]))
            aphys::collisionResponse(*this->gameBoundaryList[i], *this->gamePlatformList[0]);
    }

    // collision detection and response (target = ball)

    // game platforms
    for (unsigned int i = 0; i < this->gamePlatformList.GetSize(); ++i)
    {
        // only if enabled
        if (!this->gamePlatformList[i]->IsEnabled())
            continue;

        if (aphys::collisionCheck(*this->gamePlatformList[i], *this->gameBallList[0], deltaTime))
            aphys::collisionResponse(*this->gamePlatformList[i], *this->gameBallList[0]);
    }

    // game walls
    for (unsigned int i = 0; i < this->gameWallList.GetSize(); ++i)
    {
        // only if enabled
        if (!this->gameWallList[i]->IsEnabled())
        {
            // update remaining number
            --remainingWalls;

            continue;
        }

        if (aphys::collisionCheck(*this->gameWallList[i], *this->gameBallList[0], deltaTime))
        {
            aphys::collisionResponse(*this->gameWallList[i], *this->gameBallList[0], deltaTime);

            this->gameWallList[i]->Hit();
        }
    }

    // game boundaries
    for (unsigned int i = 0; i < this->gameBoundaryList.GetSize(); ++i)
    {
        // only if enabled
        if (!this->gameBoundaryList[i]->IsEnabled())
            continue;

        if (aphys::collisionCheck(*this->gameBoundaryList[i], *this->gameBallList[0], deltaTime))
            aphys::collisionResponse(*this->gameBoundaryList[i], *this->gameBallList[0], deltaTime);
    }

    // in the end check level status
    if (remainingBalls == 0)
        this->status = LevelStatus::FAILED;
    else if (remainingWalls == 0)
        this->status = LevelStatus::COMPLETED;

    // if level is not started, the ball needs to move with the platform -> AFTER platform collision detection and update
    if (!this->levelStarted && this->gameBallList.GetSize() > 0 && this->gamePlatformList.GetSize() > 0)
        this->gameBallList[0]->position.x = this->gamePlatformList[0]->position.x + this->gamePlatformList[0]->width / 2.0f - this->gameBallList[0]->width / 2.0f;

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
