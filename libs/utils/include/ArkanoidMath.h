
#pragma once

struct vec2f
{
    /*
	@brief
	Constructor for 2D float vector
	@param x: x coordinate
	@param y: y coordinate
	*/
    vec2f(float x, float y);

	/*
	@brief
	Default constructor for a 2D float vector (0,0)
	*/
    vec2f();

	vec2f operator*(float f)
	{
		return vec2f(this->x * f, this->y * f);
	}

	vec2f operator*(double d)
	{
		return vec2f(float(double(this->x) * d), float(double(this->y) * d));
	}

	vec2f operator+(vec2f v)
	{
		return vec2f(this->x + v.x, this->y + v.y);
	}

	vec2f& operator+=(vec2f v)
	{
		this->x = this->x + v.x;
		this->y = this->y + v.y;
		
		return *this;
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
    vec2ui(unsigned int x, unsigned int y);

	/*
	@brief
	Default constructor for a 2D unsigned int vector (0,0)
	*/
    vec2ui();

    unsigned int x;
    unsigned int y;
};
