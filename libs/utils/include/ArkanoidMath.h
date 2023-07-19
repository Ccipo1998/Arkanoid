
#pragma once

#ifndef LIB
#define LIB __declspec(dllexport)
#endif // !LIB

struct vec2f
{
    /*
	@brief
	Constructor for 2D float vector
	@param x: x coordinate
	@param y: y coordinate
	*/
    LIB vec2f(float x, float y);

	/*
	@brief
	Default constructor for a 2D float vector (0,0)
	*/
    LIB vec2f();

	LIB vec2f operator*(float f)
	{
		return vec2f(this->x * f, this->y * f);
	}

	LIB vec2f operator*(double d)
	{
		return vec2f(float(double(this->x) * d), float(double(this->y) * d));
	}

	LIB vec2f operator+(vec2f v)
	{
		return vec2f(this->x + v.x, this->y + v.y);
	}

	LIB vec2f& operator/=(float f)
	{
		this->x = this->x / f;
		this->y = this->y / f;
		
		return *this;
	}

	LIB vec2f& operator+=(vec2f v)
	{
		this->x = this->x + v.x;
		this->y = this->y + v.y;
		
		return *this;
	}

	LIB vec2f& operator-=(vec2f v)
	{
		this->x = this->x - v.x;
		this->y = this->y - v.y;
		
		return *this;
	}

	LIB vec2f operator-()
	{
		return vec2f(-this->x, -this->y);
	}

	LIB vec2f operator-(vec2f v)
	{
		return vec2f(this->x - v.x, this->y - v.y);
	}

	LIB vec2f operator/(float f)
	{
		return vec2f(this->x / f, this->y / f);
	}

    float x;
    float y;
};

struct vec2ui
{
	/*
	@brief
	Constructor for 2D unsigned int vector
	@param x: x coordinate
	@param y: y coordinate
	*/
    LIB vec2ui(unsigned int x, unsigned int y);

	/*
	@brief
	Default constructor for a 2D unsigned int vector (0,0)
	*/
    LIB vec2ui();

    unsigned int x;
    unsigned int y;
};

namespace amath
{
	/*
	@brief
	Normalize the vector
	@param vector: vector to normalize
	*/
	LIB vec2f normalize(vec2f& vector);

	/*
	@brief
	Return the power a number for an exponent
	@param number: the number to power
	@param exponent: the exponent
	*/
	LIB float pow(float number, int exponent);

	/*
	@brief
	Return the minimum between two numbers
	@param first: first number
	@param second: second number
	*/
	LIB float min(float first, float second);

	/*
	@brief
	Return the maximum between two numbers
	@param first: first number
	@param second: second number
	*/
	LIB float max(float first, float second);

	/*
	@brief
	Return the square root of the number (binary search)
	@param number: the number to square root
	*/
	LIB float sqrt(float number);

	/*
	@brief
	Return the lenght of the vector
	@param vector: the reference to the vector
	*/
	LIB float length(const vec2f& vector);

	/*
	@bried
	Return the absolute value
	@param value: the value to use
	*/
	LIB float abs(float value);

	/*
	@brief
	Clamp the value inside the range [min, max]
	@param value: the value to clamp
	@param min: the minimum returned
	@param max: the maximum returned
	*/
	LIB float clamp(float value, float min, float max);
}
