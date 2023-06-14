
#include "GameManager.h"

GameManager::GameManager()
    : score(0)
    , window(nullptr)
    , renderer(nullptr)
    , font(nullptr)
    , music(nullptr)
    {}

bool GameManager::InitializeSDL(unsigned int windowWidth, unsigned int windowHeight)
{
    // set window size
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    Uint32 windowFlags = SDL_WindowFlags::SDL_WINDOW_SHOWN;
    // Other possible useful window flags:
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_OPENGL;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_FULLSCREEN_DESKTOP;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_HIDDEN;
    // windowFlags |= SDL_WindowFlags::SDL_WINDOW_BORDERLESS;

    // Create window
    this->window = SDL_CreateWindow("MGD Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, windowFlags);
    if (this->window == nullptr) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer for window
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == nullptr) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Open the font
    this->font = TTF_OpenFont("Fonts/OpenSans-Bold.ttf", 28);
    if (this->font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    // Load music
    this->music = Mix_LoadMUS("Assets/Kmedley.mp3");
    if (this->music == nullptr) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    if (Mix_PlayMusic(this->music, -1) == -1) {
        printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    // Initialize the renderer blend mode
    SDL_SetRenderDrawBlendMode(this->renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

    // Initialize renderer color
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

void GameManager::CloseSDL()
{
    // Free global font
    TTF_CloseFont(this->font);
    this->font = nullptr;

    // Free the music
    Mix_FreeMusic(this->music);
    Mix_CloseAudio();
    this->music = nullptr;

    // Destroy window
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    this->renderer = nullptr;
    this->window = nullptr;

    // Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameManager::LoadPrefabs()
{
    // game walls
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/BlueWall.png"), 0, 0, 1));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/GreenWall.png"), 0, 0, 1));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/RedWall.png"), 0, 0, 1));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/LightBlueWall.png"), 0, 0, 2));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/OrangeWall.png"), 0, 0, 2));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/PinkWall.png"), 0, 0, 2));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/SilverWall.png"), 0, 0, 3));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/WhiteWall.png"), 0, 0, 3));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/YellowWall.png"), 0, 0, 3));
    this->WallPrefabs.Add(GameWallPrefab(MGDTexture("assets/GoldWall.png"), 0, 0, 5));

    // game backgrounds
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/BlueBackground.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/BlueBackground1.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/DarkBlueBackground.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/DarkBlueBackground1.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/DarkGreenBackground.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/GreenBackground.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/RedBackground.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/RedBackground1.png"), 0, 0));
    this->BackgroundsPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/RedBackground2.png"), 0, 0));

    // game platforms
    this->PlatformPrefabs.Add(GameRectanglePrefab(MGDTexture("assets/VausPlatform.png"), 0, 0));

    // game ball
    this->BallPrefab = GameBallPrefab(MGDTexture("assets/EnergyBall.png"), 0, .0f);
}

void GameManager::GenerateRandomLevel()
{
    this->currentLevel = Level(this->windowWidth, this->windowHeight, 10);

    this->currentLevel.SetBackground(GameRectangle(vec2f(.0f, .0f), this->BackgroundsPrefabs[0].GetTexture(), this->windowWidth, this->windowHeight));
}

Level* GameManager::GetCurrentLevel()
{
    return &this->currentLevel;
}
