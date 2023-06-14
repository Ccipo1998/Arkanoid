#include "MGDMovableTexture.h"
#include "MGDTexture.h"

MGDMovableTexture::MGDMovableTexture()
    : _posX(0)
    , _posY(0)
    , _velX(0)
    , _velY(0)
    , _path("Assets/MissingTexture.bmp") {
    _texture = new MGDTexture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    } else {
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
    }
}

MGDMovableTexture::MGDMovableTexture(std::string path)
    : _posX(0)
    , _posY(0)
    , _velX(0)
    , _velY(0)
    , _path(path) {
    _texture = new MGDTexture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    } else {
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
    }
}

MGDMovableTexture::~MGDMovableTexture() {
    // Free loaded images
    _texture->freeTexture();
    delete _texture;
}

void MGDMovableTexture::handleEvent(SDL_Event& sdlEvent) {
    // If a key was pressed
    if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0) {
        // Adjust the velocity
        switch (sdlEvent.key.keysym.sym) {
            case SDLK_UP:
            case 'w':
                _velY -= _velocity;
                break;
            case SDLK_DOWN:
            case 's':
                _velY += _velocity;
                break;
            case SDLK_LEFT:
            case 'a':
                _velX -= _velocity;

                break;
            case SDLK_RIGHT:
            case 'd':
                _velX += _velocity;

                break;
        }
    }
    // If a key was released
    else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0) {
        // Adjust the velocity

        switch (sdlEvent.key.keysym.sym) {
            case SDLK_UP:
            case 'w':
                _velY += _velocity;
                break;
            case SDLK_DOWN:
            case 's':
                _velY -= _velocity;
                break;
            case SDLK_LEFT:
            case 'a':
                _velX += _velocity;
                break;
            case SDLK_RIGHT:
            case 'd':
                _velX -= _velocity;
                break;
        }
    }
}

void MGDMovableTexture::move(double timeStep, unsigned int windowWidth, unsigned int windowHeight) {
    // Move the texture left or right
    _posX += _velX * timeStep;

    // If the texture went too far to the left or right
    if (_posX < 0) {
        //_posX = 0;
    } else if (_posX > windowWidth - _textureWidth) {
        _posX = windowHeight - _textureWidth;
    }

    // Move the texture up or down
    _posY += _velY * timeStep;

    // If the texture went too far up or down
    if (_posY < 0) {
        //_posY = 0;
    } else if (_posY > windowHeight - _textureHeight) {
        _posY = windowHeight - _textureHeight;
    }
}

void MGDMovableTexture::render() {
    // Show the texture
    _texture->render((int)_posX, (int)_posY);
}

// Sets the position of this texture (0,0 is the top left)
void MGDMovableTexture::setPosX(double posX) {
    _posX = posX;
}
void MGDMovableTexture::setPosY(double posY) {
    _posY = posY;
}

// Gets the position of this texture (0,0 is the top left)
const double MGDMovableTexture::getPosX() {
    return _posX;
}
const double MGDMovableTexture::getPosY() {
    return _posY;
}
