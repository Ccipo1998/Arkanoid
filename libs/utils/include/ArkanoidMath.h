
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
