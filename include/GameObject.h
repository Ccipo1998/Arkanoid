
#pragma once

#include "MGDTexture.h"
#include "ArkanoidMath.h"
#include "ArkanoidList.hpp"

class GameObject
{
public:

	GameObject();

	/*
	@brief
	Constructor for a generic game object
	@param position: initial position of the game object
	@param texture: pointer to the texture to render on the game object
	*/
	GameObject(vec2f position, MGDTexture* texture);

	virtual void Render() = 0;

	/*
	@brief
	Texture getter
	*/
	MGDTexture* GetTexture();

	/*
	@brief
	Check if the game object is currently enabled (i.e. considered for the updates)
	*/
	bool IsEnabled();

	/*
	@brief
	Enable the game object (i.e. considered for the updates)
	*/
	void Enable();

	/*
	@brief
	Disable the game object (i.e. not considered for the updates)
	*/
	void Disable();
	
	vec2f position;

protected:

	MGDTexture* texture;
	bool enabled;

};

class GamePrefab
{
	public:

	GamePrefab();

	/*
	@brief
	Constructor for a generic game prefab
	@param texture: the texture to apply to the game prefab
	*/
	GamePrefab(MGDTexture* texture);

	void AddTexture(MGDTexture* texture);

	/*
	@brief
	Texture getter
	*/
	MGDTexture* GetTexture();

protected:

	MGDTexture* texture;
	List<MGDTexture> textures;
};

class GameRectangle : public GameObject
{
public:

	GameRectangle();

	/*
	@brief
	Constructor for a generic game rectangle
	@param position: initial position of the game rectangle
	@param texture: the texture to render on the game rectangle
	@param width: the width of the game rectangle
	@param height: the height of the game rectangle
	*/
	GameRectangle(vec2f position, MGDTexture* texture, unsigned int width, unsigned int height);

	/*
	@brief
	Game rectangle rendering method
	*/
	void Render() override;

	unsigned int width;
	unsigned int height;

};

class GameRectanglePrefab : public GamePrefab
{
	public:

	GameRectanglePrefab();

	/*
	@brief
	Constructor for a generic game rectangle prefab
	@param texture: the texture to render on the game rectangle prefab
	@param width: the width of the game rectangle prefab
	@param height: the height of the game rectangle prefab
	*/
	GameRectanglePrefab(MGDTexture texture, unsigned int width, unsigned int height);

	unsigned int width;
	unsigned int height;
};

class GameWall : public GameRectangle
{
public:

	GameWall();

	/*
	@brief
	Constructor for a game wall
	@param position: initial position of the game object
	@param texture: the texture to render on the game object
	@param width: the width of the game wall
	@param height: the height of the game wall
	@param maxHitCount: the number of hits to destroy the game wall
	*/
	GameWall(vec2f position, MGDTexture* texture, unsigned int width, unsigned int height, unsigned int maxHitCount);

	/*
	@brief
	Hits left getter
	*/
	unsigned int GetHitCount();

protected:

	unsigned int hitCount;

	List<MGDTexture*> textures;

};

class GameWallPrefab: public GameRectanglePrefab
{
	public:

	GameWallPrefab();

	/*
	@brief
	Constructor for a game wall prefab
	@param texture: the texture to render on the game object
	@param width: the standard width of the game wall prefab
	@param height: the standard height of the game wall prefab
	@param maxHitCount: the number of hits to destroy the game wall
	*/
	GameWallPrefab(MGDTexture texture, unsigned int width, unsigned int height, unsigned int maxHitCount);

	/*
	@brief
	Add a new texture to display instead the default one when the game wall prefab reached a certain number of hits left
	@param atHitCount: at which number of hits left the new texture should be displayed
	@param texture: the new texture
	*/
	void AddTexture(unsigned int atHitCount, MGDTexture texture);

	unsigned int maxHitCount;
};

class GameBall : public GameObject
{
public:

	GameBall();

	/*
	@brief
	Constructor for a game ball
	@param position: initial position of the game ball
	@param texture: the texture to render on the game ball
	@param size: the diameter of the ball
	@param speed: the movement speed of the game ball
	*/
	GameBall(vec2f position, MGDTexture* texture, unsigned int size, float speed);

	/*
	@brief
	Current velocity getter
	*/
	vec2f GetVelocity();

	/*
	@brief
	Game ball rendering method
	*/
	void Render() override;

	unsigned int size;
	float speed;

private:

	vec2f velocity;

};

class GameBallPrefab : public GamePrefab
{

public:

	GameBallPrefab();

	/*
	@brief
	Constructor for a game ball prefab
	@param texture: the texture to render on the game ball prefab
	@param size: the diameter of the ball
	@param speed: the movement speed of the game ball prefab
	*/
	GameBallPrefab(MGDTexture texture, unsigned int size, float speed);

	unsigned int size;
	float speed;

};

class GamePlatform : public GameRectangle // TODO: implement input system and abilities
{

};

class GamePlatformPrefab : public GameRectanglePrefab // idk if it is useful
{

};
