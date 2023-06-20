
#include "ArkanoidPhysics.h"

namespace aphys
{
    float epsilon = .0001f;

    void collisionResponse(const GameRect& staticRect, GameBall& ball, double deltaTime)
    {
        /*
        // retrieve old position
        vec2f oldPos = ball.position - ball.GetDirection() * ball.speed * deltaTime;

        // compute intersection point
        if (ball.GetDirection().x > .0f && ball.GetDirection().y > .0f)
        {
            // possible intersection on up or left edge

            // this edge is the trajectory of the ball
            vec2f p1 = vec2f(oldPos);
            vec2f p2 = ball.position;
            // upper edge
            vec2f q1 = staticRect.position;
            vec2f q2 = vec2f(staticRect.position.x + staticRect.width, staticRect.position.y);


        }*/

        // get length differences
        float deltaX = staticRect.width - amath::abs(staticRect.position.x - ball.position.x);
        float deltaY = staticRect.height - amath::abs(staticRect.position.y - ball.position.y);

        // if the ball is already inside the rectangle it must be shifted back
        if ((deltaX >= .0f + epsilon && deltaX <= .0f - epsilon) || (deltaY >= .0f + epsilon && deltaY <= .0f - epsilon))
        {
            ball.position -= ball.GetDirection() * amath::length(vec2f(deltaX, deltaY));
        }

        // select the correct way to flip direction
        if (deltaX < deltaY)
            ball.SetDirection(vec2f(-ball.GetDirection().x, ball.GetDirection().y));
        else if (deltaY < deltaX)
            ball.SetDirection(vec2f(ball.GetDirection().x, -ball.GetDirection().y));
        else
            ball.SetDirection(-ball.GetDirection());

        // movement in new direction to avoid new immediate collisions after collision response
        ball.position += ball.GetDirection() * ball.speed * deltaTime;
    }

    bool collisionCheck(const GameRect& rect1, GameRect& rect2)
    {
        bool checkX = intersection(rect1.position.x, rect1.position.x + rect1.width, rect2.position.x, rect2.position.x + rect2.width);
        bool checkY = intersection(rect1.position.y, rect1.position.y + rect1.height, rect2.position.y, rect2.position.y + rect2.height);

        return checkX && checkY;
    }

    bool intersection(float x1, float x2, float x3, float x4)
    {
        if (x2 < x3)
            return false;

        if (x4 < x1)
            return false;

        return true;
    }
}
