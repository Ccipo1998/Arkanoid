#pragma once

#include <SDL_ttf.h>
#include <string>

// Texture wrapper class
class MGDTexture {
public:
    // Initializes variables
    MGDTexture();

    // Initializes variables and tries to load the texture by the path
    MGDTexture(std::string path);

    // Deallocates memory
    ~MGDTexture();

    // Loads image at specified path
    bool loadFromFile(std::string path);

    // Loads image into pixel buffer
    bool loadPixelsFromFile(std::string path);

    // Creates image from preloaded pixels
    bool loadFromPixels();

    // Creates image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

    // Creates blank texture
    bool createBlank(int width, int height, SDL_TextureAccess access);

    // Deallocates texture
    void freeTexture();

    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    // Set blending
    void setBlendMode(SDL_BlendMode blending);

    // Set alpha modulation
    void setAlpha(Uint8 alpha);

    // Renders texture at given point
    void render(int x = 0, int y = 0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Renders texture at given point using the same parameters of the original
    // RenderCopyEx
    void renderCopyEx(
        SDL_Rect* destinationRect = NULL, SDL_Rect* clipRect = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Set self as render target
    void setAsRenderTarget();

    // Gets image dimensions
    int getWidth();
    int getHeight();

    // Pixel accessors
    Uint32* getPixels32();
    Uint32 getPixel32(Uint32 x, Uint32 y);
    Uint32 getPitch32();
    void copyRawPixels32(void* pixels);
    bool lockTexture();
    bool unlockTexture();

private:
    // The actual hardware texture
    SDL_Texture* _texture;

    // Surface pixels
    SDL_Surface* _surfacePixels;

    // Raw pixels
    void* _rawPixels;
    int _rawPitch;

    // Image dimensions
    int _width;
    int _height;
};
