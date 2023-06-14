/*
Requisiti minimi progetto finale:
no memory leak
no using
no container
*/

// All the SDL includes we need
#include "SDL.h"
#undef main

#include <cstdio> //Some utilities for the log
#include <memory> // Needed for the smart pointers

#include "MGDMovableTexture.h"
#include "MGDTexture.h"
#include "MGDTimer.h"

#include "Singleton.hpp"
#include "GameManager.h"

int main() {

    // Game loop flag
    bool quitGame = false;

    // init game manager
    GameManager* manager = Singleton<GameManager>::GetInstance();

    // Start up SDL and create window
    if (!manager->InitializeSDL(480, 640)) {
        printf("Failed to initialize!\n");
        
        // Free resources and close SDL
        manager->CloseSDL();

        return 0;
    }

    // loading assets and levels
    manager->LoadPrefabs();
    manager->GenerateRandomLevel();

    // SDL Event handler
    SDL_Event sdlEvent;

    // keeps track of time between steps
    MGDTimer stepTimer;
    
    // game loop
    while(!quitGame)
    {
        // handle events
        while (SDL_PollEvent(&sdlEvent) != 0) {
            // User requests quit
            if (sdlEvent.type == SDL_QUIT)
                quitGame = true;
        }

        // Get the delta time in milliseconds
        Uint32 deltaTimeMs = stepTimer.getTicks();
        // Calculate the delta time in seconds
        double deltaTimeS = deltaTimeMs * 0.001;
        // Restart step timer
        stepTimer.start();

        // Clear screen
        SDL_SetRenderDrawColor(manager->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(manager->renderer);

        SDL_Rect background = 
        { manager->GetCurrentLevel()->GetBackground()->position.x, manager->GetCurrentLevel()->GetBackground()->position.y,
            manager->GetCurrentLevel()->GetBackground()->width, manager->GetCurrentLevel()->GetBackground()->height };
        MGDTexture* tex = manager->GetCurrentLevel()->GetBackground()->GetTexture();
        tex->renderCopyEx(&background);

        // update screen
        SDL_RenderPresent(manager->renderer);
    }

    // Free resources and close SDL
    manager->CloseSDL();

    return 0;
}

