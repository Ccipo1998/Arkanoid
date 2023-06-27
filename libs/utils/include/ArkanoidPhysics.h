
#pragma once

#include "GameObject.h"

struct ray2f
{
    vec2f origin;
    vec2f direction;
    double length;  
};

struct inter2f
{
    bool hit;
    vec2f point;
    float distance;
    vec2f bounce;
};

namespace aphys
{
    /*
    @brief
    Perform the intersection test between a ray and an edge, storing the intersection's info
    @param ray: reference to the ray
    @param point1: the reference to the first point of the edge
    @param point2: the reference to the second point of the edge
    @param inter: the reference to the intersection structure
    */
    void intersectionRayEdge(ray2f& ray, vec2f& point1, vec2f& point2, inter2f& inter);

    /*
    @brief
    Physical collision response between a game platform and a game ball
    @param platform: the reference to the game platform
    @param ball: the reference to the game ball
    */
    void collisionResponse(const GamePlatform& platform, GameBall& ball);

    /*
    @brief
    Physical collision response between a static game rectangle and a game platform
    @param staticRect: reference to the game rectangle which doesn't move
    @param platform: reference to the game platform
    */
    void collisionResponse(const GameRect& staticRect, GamePlatform& platform);

    void collisionResponse(GameBall& ball, inter2f& inter, double deltaTime);

    /*
    @brief
    Check if a game rectangles and a game ball collided, taking into account last ball's movement, and returning intersection's info
    @param rect: the game rectangle
    @param ball: the game ball
    @param deltaTime: the time passed from last frame
    */
    inter2f collisionCheck(const GameRect& rect, GameBall& ball, double deltaTime);

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
