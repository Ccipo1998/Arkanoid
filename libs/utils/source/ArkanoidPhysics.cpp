
#include "ArkanoidPhysics.h"

namespace aphys
{
    float epsilon = .0001f;

    void collisionResponse(const GameRect& staticRect, GameBall& ball, double deltaTime)
    {
        float deltaX = .0f;
        float deltaY = .0f;

        if (ball.GetDirection().x >= .0f && ball.GetDirection().y >= .0f)
        {
            // possible intersection on up or left edge
            deltaX = amath::abs(staticRect.position.x - ball.position.x) + ball.width;
            deltaY = amath::abs(staticRect.position.y - ball.position.y) + ball.height;
        }
        else if (ball.GetDirection().x <= .0f && ball.GetDirection().y >= .0f)
        {
            // possible intersection on up or right edge
            deltaX = staticRect.width - amath::abs(staticRect.position.x - ball.position.x);
            deltaY = amath::abs(staticRect.position.y - ball.position.y) + ball.height;
        }
        else if (ball.GetDirection().x >= .0f && ball.GetDirection().y <= .0f)
        {
            // possible intersection on bottom or left edge
            deltaX = amath::abs(staticRect.position.x - ball.position.x) + ball.width;
            deltaY = staticRect.height - amath::abs(staticRect.position.y - ball.position.y);
        }
        else if (ball.GetDirection().x <= .0f && ball.GetDirection().y <= .0f)
        {
            // possible intersection on bottom or right edge
            deltaX = staticRect.width - amath::abs(staticRect.position.x - ball.position.x);
            deltaY = staticRect.height - amath::abs(staticRect.position.y - ball.position.y);
        }

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
