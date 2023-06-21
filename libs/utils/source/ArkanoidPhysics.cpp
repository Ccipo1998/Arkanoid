
#include "ArkanoidPhysics.h"

namespace aphys
{
    float epsilon = .0001f;

    void collisionResponse(const GameRect& staticRect, GamePlatform& platform)
    {
        // only checking on x
        float distanceBefore = staticRect.position.x - (platform.position.x - platform.GetVelocity().x);

        // 1.0f added to avoid another collision at next frame
        if (distanceBefore > .0f)
            platform.position.x = staticRect.position.x - platform.width + 1.0f;
        else if (distanceBefore < .0f)
            platform.position.x = staticRect.position.x + staticRect.width + 1.0f;
    }

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

    bool collisionCheck(const GameRect& rect, GameBall& ball, double deltaTime)
    {
        // points need to be placed in the right order inside the call to intersection()
        float minX = amath::min(ball.position.x, ball.position.x - (ball.GetDirection().x * ball.speed * deltaTime));
        float maxX = amath::max(ball.position.x - (ball.GetDirection().x * ball.speed * deltaTime), ball.position.x + ball.width);
        float minY = amath::min(ball.position.y, ball.position.y - (ball.GetDirection().y * ball.speed * deltaTime));
        float maxY = amath::max(ball.position.y - (ball.GetDirection().y * ball.speed * deltaTime), ball.position.y + ball.height);
        
        bool checkX = intersection(rect.position.x, rect.position.x + rect.width, minX, maxX);
        bool checkY = intersection(rect.position.y, rect.position.y + rect.height, minY, maxY);
    
        return checkX && checkY;
    }

    bool collisionCheck(const GameRect& rect, GamePlatform& platform)
    {
        // points need to be placed in the right order inside the call to intersection()
        float minX = amath::min(platform.position.x, platform.position.x - platform.GetVelocity().x);
        float maxX = amath::max(platform.position.x - platform.GetVelocity().x, platform.position.x + platform.width);
        float minY = amath::min(platform.position.y, platform.position.y - platform.GetVelocity().y);
        float maxY = amath::max(platform.position.y - platform.GetVelocity().y, platform.position.y + platform.height);
        
        bool checkX = intersection(rect.position.x, rect.position.x + rect.width, minX, maxX);
        bool checkY = intersection(rect.position.y, rect.position.y + rect.height, minY, maxY);
    
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
