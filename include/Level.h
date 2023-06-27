
#pragma once

#include "GameObject.h"
#include "ArkanoidList.hpp"

enum class LevelStatus
{
    RUNNING,
    COMPLETED,
    FAILED
};

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

    /*
    @brief
    Level walls space setter
    @param wallsSpace: the game rect representing the space for the game walls
    */
    void SetWallsSpace(GameRect* wallsSpace);

    /*
    @brief
    Level walls space getter
    */
    GameRect* GetWallsSpace();

    /*
    @brief
    Level platform space setter
    @param platformSpace: the game rect representing the space for the game platforms
    */
    void SetPlatformSpace(GameRect* platformSpace);

    /*
    @brief
    Level platform space getter
    */
    GameRect* GetPlatformSpace();

    /*
    @brief
    Check the status of the current level. Possible output: RUNNING, COMPLETED, FAILED
    */
    LevelStatus GetLevelStatus();

    /*
    @brief
    Handle events sending them to the targets
    @param sdlEvent: reference to the event to handle
    @param deltaTime: the time passed from the last frame
    */
    void HandleEvents(SDL_Event& sdlEvent);

    /*
    @brief
    Update all the objects of the level
    @param deltaTime: the time passed from the last frame
    */
    void Update(double deltaTime);

    /*
    @brief
    Call render functions of all the active game objects of the level
    */
    void Render();

    ~Level();

private:

    List<GameWall*> gameWallList;
    List<GameBall*> gameBallList;
    List<GamePlatform*> gamePlatformList;
    List<GameRect*> gameBoundaryList;
    
    GameRect* background;
    GameRect* wallsSpace;
    GameRect* platformSpace;

    bool levelStarted;

    LevelStatus status;

};
