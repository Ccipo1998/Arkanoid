
#pragma once

#include "MGDTexture.h"
#include "ArkanoidMath.h"
#include "ArkanoidList.hpp"

class GameObject
{
public:

	GameObject();

	virtual void Update() = 0;

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

protected:

	bool enabled;

};

class GamePrefab
{
	public:

	GamePrefab();

	/*
	@brief
	Add a texture for the game prefab
	@param texture: the pointer to the texture to add
	*/
	void AddTexture(MGDTexture* texture);

	/*
	@brief
	Current texture getter
	*/
	MGDTexture* GetTexture();

	/*
	@brief
	Change the current selected texture
	@param index: the index of the texture to select among the textures available for the game prefab
	*/
	void SetTexture(unsigned int index);

	~GamePrefab();

protected:

	unsigned int texIndex;
	List<MGDTexture*> textures;
};

class GameRect : public GameObject
{
public:

	GameRect();

	/*
	@brief
	Constructor for a generic game rectangle
	@param position: position of the game rectangle
	@param width: the width of the game rectangle
	@param height: the height of the game rectangle
	@param prefab: the pointer to the prefab (for textures)
	*/
	GameRect(vec2f position, unsigned int width, unsigned int height, GamePrefab* prefab);

	/*
	@brief
	Game rectangle generic rendering method
	*/
	void Render();
	
	/*
	@brief
	Linked Game Prefab getter
	*/
	GamePrefab* GetPrefab();

	/*
	@brief
	Operations to execute at each frame
	*/
	void Update() override;

	~GameRect();

	vec2f position;
	unsigned int width;
	unsigned int height;

protected:

	GamePrefab* prefab;

};

class GameWallPrefab : public GamePrefab
{

public:

	GameWallPrefab();

	/*
	@brief
	Initialization constructor
	@param maxHitCount: the maximum number of hit for the game wall
	*/
	GameWallPrefab(unsigned int maxHitCount);

	/*
	@brief
	Max hit counter setter
	@param: the maximum number of hits for the game wall
	*/
	void SetMaxHitCount(unsigned int maxHitCount);

	/*
	@brief
	Max hit counter getter
	*/
	unsigned int GetMaxHitCount();

protected:

	unsigned int maxHitCount;

};

class GameWall : public GameRect
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
	GameWall(vec2f position, unsigned int width, unsigned int height, GameWallPrefab* prefab);

	/*
	@brief
	Hits left getter
	*/
	unsigned int GetHitCount();

	/*
	Decrease the hit count by one
	*/
	void Hit();

	/*
	@brief
	Operations to execute at each frame
	*/
	void Update() override;

private:

	unsigned int hitCount;

};

class GameBall : public GameRect
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
	GameBall(vec2f position, unsigned int size, GamePrefab* prefab, float speed);

	/*
	@brief
	Current velocity getter
	*/
	vec2f GetVelocity();

	/*
	@brief
	Operations to execute at each frame
	*/
	void Update() override;

	float speed;

private:

	vec2f velocity;

};

class GamePlatform : public GameRect // TODO: implement input system and abilities
{

};
