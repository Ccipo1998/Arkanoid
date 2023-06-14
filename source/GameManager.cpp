
#include "GameManager.h"

GameManager::GameManager()
    : score(0)
    , window(nullptr)
    , renderer(nullptr)
    , font(nullptr)
    , music(nullptr)
    , BallPrefab(nullptr)
    , currentLevel(nullptr)
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
    this->window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowWidth, this->windowHeight, windowFlags);
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
    this->WallPrefabs.Add(new GameWallPrefab(1));
    this->WallPrefabs[0]->AddTexture(new MGDTexture("assets/BlueWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(1));
    this->WallPrefabs[1]->AddTexture(new MGDTexture("assets/GreenWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(1));
    this->WallPrefabs[2]->AddTexture(new MGDTexture("assets/RedWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(2));
    this->WallPrefabs[3]->AddTexture(new MGDTexture("assets/LightBlueWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(2));
    this->WallPrefabs[4]->AddTexture(new MGDTexture("assets/OrangeWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(2));
    this->WallPrefabs[5]->AddTexture(new MGDTexture("assets/PinkWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(3));
    this->WallPrefabs[6]->AddTexture(new MGDTexture("assets/SilverWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(3));
    this->WallPrefabs[7]->AddTexture(new MGDTexture("assets/WhiteWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(3));
    this->WallPrefabs[8]->AddTexture(new MGDTexture("assets/YellowWall.png"));
    this->WallPrefabs.Add(new GameWallPrefab(5));
    this->WallPrefabs[9]->AddTexture(new MGDTexture("assets/GoldWall.png"));

    // game backgrounds
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[0]->AddTexture(new MGDTexture("assets/BlueBackground.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[1]->AddTexture(new MGDTexture("assets/BlueBackground1.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[2]->AddTexture(new MGDTexture("assets/DarkBlueBackground.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[3]->AddTexture(new MGDTexture("assets/DarkBlueBackground1.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[4]->AddTexture(new MGDTexture("assets/DarkGreenBackground.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[5]->AddTexture(new MGDTexture("assets/GreenBackground.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[6]->AddTexture(new MGDTexture("assets/RedBackground.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[7]->AddTexture(new MGDTexture("assets/RedBackground1.png"));
    this->BackgroundsPrefabs.Add(new GamePrefab());
    this->BackgroundsPrefabs[8]->AddTexture(new MGDTexture("assets/RedBackground2.png"));

    // game platforms
    this->PlatformPrefabs.Add(new GamePrefab());
    this->PlatformPrefabs[0]->AddTexture(new MGDTexture("assets/VausPlatform.png"));
    this->PlatformPrefabs.Add(new GamePrefab());
    this->PlatformPrefabs[1]->AddTexture(new MGDTexture("assets/VausLargePlatform.png"));

    // game ball
    this->BallPrefab = new GamePrefab();
    this->BallPrefab->AddTexture(new MGDTexture("assets/EnergyBall.png"));
}

void GameManager::GenerateRandomLevel()
{
    this->currentLevel = new Level(this->windowWidth, this->windowHeight, 10);

    this->currentLevel->SetBackground(new GameRect(vec2f(.0f, .0f), this->windowWidth, this->windowHeight, this->BackgroundsPrefabs[0]));
}

Level* GameManager::GetCurrentLevel()
{
    return this->currentLevel;
}

GameManager::~GameManager()
{
    delete this->window;
    delete this->renderer;
    delete this->font;
    delete this->music;

    // the lists free their memory and the memory of the object contained by themselves

    delete this->BallPrefab;
    delete this->currentLevel;
}
