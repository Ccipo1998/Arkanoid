
#include "arkanoidMath.h"

vec2f::vec2f(float x, float y)
    : x(x)
    , y(y)
    {}

vec2f::vec2f()
    : x(.0f)
    , y(.0f)
    {}
    
vec2ui::vec2ui()
    : x(0)
    , y(0)
    {}

vec2ui::vec2ui(unsigned int x, unsigned int y)
    : x(x)
    , y(y)
    {}

namespace amath
{
    float epsilon = .0001f;

    float pow(float number, int exponent)
    {
        if (exponent == 0)
            return 1.0f;

        float result = number;

        if (exponent < 0)
        {
            exponent = -exponent;
            result = 1.0f / number;
        }

        for (int i = 1; i < exponent; ++i)
            result *= number;

        return result;
    }

    float min(float first, float second)
    {
        if (first <= second)
            return first;

        return second;
    }

    float max(float first, float second)
    {
        if (first >= second)
            return first;

        return second;
    }

    float sqrt(float number)
    {
        // Max and min are used to take into account numbers less than 1
        float lo = min(1, number), hi = max(1, number), mid;

        // Update the bounds to be off the target by a factor of 10
        while(100 * lo * lo < number) lo *= 10.0f;
        while(0.01 * hi * hi > number) hi *= 0.1f;

        for(int i = 0 ; i < 100 ; i++){
            mid = (lo+hi)/2;
            if(mid*mid == number) return mid;
            if(mid*mid > number) hi = mid;
            else lo = mid;
        }
        return mid;
    }

    float length(const vec2f& vector)
    {
        return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    }

    vec2f normalize(vec2f& vector)
    {
        return vector / length(vector);
    }

    float abs(float value)
    {
        if (value >= .0f)
            return value;

        return -value;
    }

    float clamp(float value, float min, float max)
    {
        if (value <= min)
            return min;

        if (value >= max)
            return max;

        return value;
    }
}
