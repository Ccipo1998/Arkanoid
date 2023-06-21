
#pragma once

#include "GameObject.h"

namespace aphys
{
    /*
    @brief
    Physical collision response between a static game rectangle and a game platform
    @param staticRect: reference to the game rectangle which doesn't move
    @param platform: reference to the game platform
    */
    void collisionResponse(const GameRect& staticRect, GamePlatform& platform);

    /*
    @brief
    Physical collision response between a static game rectangle and a game ball
    @param staticRect: reference to the game rectangle which doesn't move
    @param movableRect: reference to the game ball
    */
    void collisionResponse(const GameRect& staticRect, GameBall& ball, double deltaTime);

    /*
    @brief
    Check if a game rectangles and a game ball collided, taking into account last ball's movement
    @param rect: the game rectangle
    @param ball: the game ball
    @param deltaTime: the time passed from last frame
    */
    bool collisionCheck(const GameRect& rect, GameBall& ball, double deltaTime);

    /*
    @brief
    Check if a game rectangles and a game platform collided, taking into account last platform's movement
    @param rect: the game rectangle
    @param ball: the game platform
    */
    bool collisionCheck(const GameRect& rect, GamePlatform& platform);

    /*
    @brief
    Check intersection between two edges on a single dimension
    @param x1: coordinate of the first point of the first edge
    @param x2: coordinate of the second point of the first edge
    @param x3: coordinate of the first point of the second edge
    @param x4: coordinate of the second point of the second edge
    */
    bool intersection(float x1, float x2, float x3, float x4);
}
