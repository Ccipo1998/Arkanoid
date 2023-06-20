
#pragma once

#include "GameObject.h"

namespace aphys
{
    /*
    @brief
    Physical collision response between a static game rectangle and a movable game rectangle
    @param staticRect: reference to the game rectangle which doesn't move
    @param movableRect: reference to the game rectangle to move
    */
    void collisionResponse(const GameRect& staticRect, GameBall& movableRect, double deltaTime);

    /*
    @brief
    Check if the two game rectangles are colliding
    @param rect1: the first game rectangle
    @param rect2: the second game rectangle
    */
    bool collisionCheck(const GameRect& rect1, GameRect& rect2);

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
