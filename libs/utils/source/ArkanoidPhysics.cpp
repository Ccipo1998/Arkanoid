
#include "ArkanoidPhysics.h"

namespace aphys
{
    float epsilon = .0001f;

    void intersectionRayEdge(ray2f& ray, vec2f& point1, vec2f& point2, inter2f& inter)
    {
        vec2f v1 = ray.origin - point1;
        vec2f v2 = point2 - point1;
        vec2f v3 = vec2f(-ray.direction.y, ray.direction.x);

        float prova = (v2.x * v1.y - v2.y * v1.x);
        float t1 = (v2.x * v1.y - v2.y * v1.x) / amath::dot(v2, v3);
        float t2 = amath::dot(v1, v3) / amath::dot(v2, v3);

        if (t1 > ray.length)
        {
            inter = { false };
            return;
        }

        if (t1 >= .0f && .0f <= t2 && t2 <= 1.f)
        {
            inter = { true, ray.origin + ray.direction * t1, t1 };
            return;
        }

        inter = { false };
    }

    void collisionResponse(const GamePlatform& platform, GameBall& ball)
    {
        // special collision between the platform and the ball
        // always up but with the x defined by the position of the collision compared to the center of the platform
        
        float maximumDistX = platform.width / 2.0f + ball.width / 2.0f;
        float signedDistX = ((ball.position.x + (ball.width / 2.0f)) - (platform.position.x + (platform.width / 2.0f)));
        float clampedDistX = amath::clamp(signedDistX / maximumDistX, -1.0f, 1.0f);

        ball.SetDirection(vec2f(clampedDistX, -1.0f));
    }

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

    void collisionResponse(GameBall& ball, inter2f& inter, double deltaTime)
    {
        // shift back the ball
        ball.position -= ball.GetDirection() * ball.speed * deltaTime;

        // time to collision
        double deltaT = inter.distance * deltaTime / (ball.speed * deltaTime);

        // move ball to collision
        ball.position += ball.GetDirection() * ball.speed * deltaT;

        // set new ball dir
        ball.SetDirection(ball.GetDirection() * inter.bounce);

        // move the ball in the right direction
        if (deltaT == deltaTime)
            ball.position += ball.GetDirection(); // * 1.f
        else
            ball.position += ball.GetDirection() * ball.speed * (deltaTime - deltaT);
    }

    inter2f collisionCheck(const GameRect& rect, GameBall& ball, double deltaTime)
    {
        if (ball.GetDirection() == vec2f())
            return inter2f { false };

        vec2f rectPoint;
        vec2f ballPoint;
        vec2f dir;

        ray2f ray;
        double rayLength;
        vec2f point1;
        vec2f point2;
        inter2f inter;
        float dot;
        vec2f perp;
        vec2f oldPos;

        // old ball position
        oldPos = ball.position - ball.GetDirection() * ball.speed * deltaTime;

        // ray length
        rayLength = ball.speed * deltaTime;

        // ball coming from upper left
        if (ball.GetDirection().x >= .0f && ball.GetDirection().y >= .0f)
        {
            // use upper left point of the rect
            rectPoint = rect.position;
            // use bottom right point of the ball
            ballPoint = oldPos + vec2f(ball.width, ball.height);

            // check if the collision happened on left or top edge of the rect
            dir = amath::normalize(rectPoint - ballPoint);
            // perpendicular vector to dir and dot with the ball direction
            perp = vec2f(-dir.y, dir.x);
            dot = amath::dot(ball.GetDirection(), perp);

            // compare perpendicular and ball directions
            if (dot < .0f)
            {
                // intersection test on top edge
                point1 = rect.position;
                point2 = vec2f(point1.x + rect.width, point1.y);

                // ray from lower left ball's point
                ray = { vec2f(oldPos.x, oldPos.y + ball.height), ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(1.f, -1.f);
            }
            else if (dot > .0f)
            {
                // intersection test on left edge
                point1 = rect.position;
                point2 = vec2f(point1.x, point1.y + rect.height);

                // ray from top right ball's point
                ray = { vec2f(oldPos.x + ball.width, oldPos.y), ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(-1.f, 1.f);
            }
            else
            {
                // same directions -> intersection point is the top left point of the rect
                inter = { true, rectPoint, amath::length(ballPoint - rectPoint) };
                // add bounce to intersection
                inter.bounce = vec2f(-1.f, -1.f);
            }
        }
        // ball coming from upper right
        else if (ball.GetDirection().x <= .0f && ball.GetDirection().y >= .0f)
        {
            // use upper right point of the rect
            rectPoint = vec2f(rect.position.x + rect.width, rect.position.y);
            // use bottom left point of the ball
            ballPoint = oldPos + vec2f(.0f, ball.height);

            // check if the collision happened on right or top edge of the rect
            dir = amath::normalize(rectPoint - ballPoint);
            // perpendicular vector to dir and dot with the ball direction
            perp = vec2f(-dir.y, dir.x);
            dot = amath::dot(ball.GetDirection(), perp);

            // compare perpendicular and ball directions
            if (dot < .0f)
            {
                // intersection test on right edge
                point1 = vec2f(rect.position.x + rect.width, rect.position.y);
                point2 = vec2f(point1.x, point1.y + rect.height);

                // ray from upper left ball's point
                ray = { oldPos, ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(-1.f, 1.f);
            }
            else if (dot > .0f)
            {
                // intersection test on top edge
                point1 = rect.position;
                point2 = vec2f(point1.x + rect.width, point1.y);

                // ray from bottom right ball's point
                ray = { oldPos + vec2f(ball.width, ball.height), ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(1.f, -1.f);
            }
            else
            {
                // same directions -> intersection point is the top rigth point of the rect
                inter = { true, rectPoint, amath::length(ballPoint - rectPoint) };
                // add bounce to intersection
                inter.bounce = vec2f(-1.f, -1.f);
            }
        }
        // ball coming from lower left
        else if (ball.GetDirection().x >= .0f && ball.GetDirection().y <= .0f)
        {
            // use lower left point of the rect
            rectPoint = vec2f(rect.position.x, rect.position.y + rect.height);
            // use top right point of the ball
            ballPoint = vec2f(oldPos.x + ball.width, oldPos.y);

            // check if the collision happened on left or bottom edge of the rect
            dir = amath::normalize(rectPoint - ballPoint);

            // perpendicular vector to dir and dot with the ball direction
            perp = vec2f(-dir.y, dir.x);
            dot = amath::dot(ball.GetDirection(), perp);

            // compare perpendicular and ball directions
            if (dot > .0f)
            {
                // intersection on bottom edge
                point1 = vec2f(rect.position.x, rect.position.y + rect.height);
                point2 = vec2f(point1.x + rect.width, point1.y);

                // ray from top left ball's point
                ray = { oldPos, ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(1.f, -1.f);
            }
            else if (dot < .0f)
            {
                // intersection on left edge
                point1 = rect.position;
                point2 = vec2f(point1.x, point1.y + rect.height);

                // ray from lower right ball's point
                ray = { oldPos + vec2f(ball.width, ball.height), ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(-1.f, 1.f);
            }
            else
            {
                // same directions -> intersection point is the bottom left point of the rect
                inter = { true, rectPoint, amath::length(ballPoint - rectPoint) };
                // add bounce to intersection
                inter.bounce = vec2f(-1.f, -1.f);
            }
        }
        // ball coming from lower right
        else
        {
            // use lower right point of the rect
            rectPoint = vec2f(rect.position.x + rect.width, rect.position.y + rect.height);
            // use top left point of the ball
            ballPoint = oldPos;

            // check if the collision happened on right or bottom edge of the rect
            dir = amath::normalize(rectPoint - ballPoint);

            // perpendicular vector to dir and dot with the ball direction
            perp = vec2f(-dir.y, dir.x);
            dot = amath::dot(ball.GetDirection(), perp);

            // compare perpendicular and ball directions
            if (dot > .0f)
            {
                // intersection on right edge
                point1 = vec2f(rect.position.x + rect.width, rect.position.y);
                point2 = vec2f(point1.x, point1.y + rect.height);

                // ray from lower left ball's point
                ray = { vec2f(oldPos.x, oldPos.y + ball.height), ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(-1.f, 1.f);
            }
            else if (dot < .0f)
            {
                // intersection on bottom edge
                point1 = vec2f(rect.position.x, rect.position.y + rect.height);
                point2 = vec2f(point1.x + rect.width, point1.y);

                // ray from upper right ball's point
                ray = { oldPos + vec2f(ball.width, .0f), ball.GetDirection(), rayLength };
                intersectionRayEdge(ray, point1, point2, inter);

                // add bounce to intersection
                inter.bounce = vec2f(1.f, -1.f);
            }
            else
            {
                // same directions -> intersection point is the bottom right point of the rect
                inter = { true, rectPoint, amath::length(ballPoint - rectPoint) };
                // add bounce to intersection
                inter.bounce = vec2f(-1.f, -1.f);
            }
        }

        return inter;
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
