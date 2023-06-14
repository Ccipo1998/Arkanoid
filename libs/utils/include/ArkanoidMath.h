
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

    float x;
    float y;
};
