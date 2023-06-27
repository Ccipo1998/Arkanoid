/*
Requisiti minimi progetto finale:
no memory leak
no using
no container
*/

// for memory leaks check
#ifdef BUILD_DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new DEBUG_NEW
#endif

// All the SDL includes we need
#include "SDL.h"
#undef main // for linking error

#include <cstdio> //Some utilities for the log
#include <memory> // Needed for the smart pointers

#include "MGDMovableTexture.h"
#include "MGDTexture.h"
#include "MGDTimer.h"

#include "Singleton.hpp"
#include "GameManager.h"
#include "Level.h"

int main() {

    #ifdef BUILD_DEBUG
        // enable memory leak detection
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    // Game loop flag
    bool quitGame = false;

    // init game manager
    GameManager* manager = Singleton<GameManager>::GetInstance();

    // Start up SDL and create window
    if (!manager->InitializeSDL(680, 740)) {
        printf("Failed to initialize!\n");
        
        // Free resources and close SDL
        manager->CloseSDL();

        return 0;
    }

    // hide mouse cursor
    SDL_ShowCursor(SDL_DISABLE);
    // take mouse outside window
    SDL_CaptureMouse(SDL_TRUE);

    // loading assets and levels
    manager->LoadPrefabs();
    manager->GenerateRandomLevel();

    // SDL Event handler
    SDL_Event sdlEvent;

    // keeps track of time between steps
    MGDTimer stepTimer;

    // current level status
    LevelStatus currentStatus;

    // game loop
    while(!quitGame)
    {
        // Get the delta time in milliseconds
        Uint32 deltaTimeMs = stepTimer.getTicks();
        // Calculate the delta time in seconds
        double deltaTimeS = deltaTimeMs * 0.001;
        // Restart step timer
        stepTimer.start();

        // handle events
        while (SDL_PollEvent(&sdlEvent) != 0) {
            // User requests quit
            if (sdlEvent.type == SDL_QUIT)
                quitGame = true;

            manager->GetCurrentLevel()->HandleEvents(sdlEvent);
        }

        // check current level status
        currentStatus = manager->GetCurrentLevel()->GetLevelStatus();
        switch (currentStatus)
        {
        case LevelStatus::COMPLETED:
            
            // next level
            manager->GenerateRandomLevel();

            break;

        case LevelStatus::FAILED:

            // game over
            quitGame = true;

            break;
        
        default:
            break;
        }

        // Clear screen
        SDL_SetRenderDrawColor(manager->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(manager->renderer);

        // level update
        manager->GetCurrentLevel()->Update(deltaTimeS);

        // level rendering
        manager->GetCurrentLevel()->Render();

        // update screen
        SDL_RenderPresent(manager->renderer);
    }

    // Free resources and close SDL
    manager->CloseSDL();

    delete manager;

    #ifdef BUILD_DEBUG
        // query memory leaks
        _CrtDumpMemoryLeaks();
    #endif

    return 0;
}


