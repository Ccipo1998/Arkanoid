
#include "GameObject.h"

GameObject::GameObject()
	: position(vec2f(.0f, .0f))
	, texture(nullptr)
	{}

GameObject::GameObject(vec2f position, MGDTexture* texture)
	: position(position)
	, texture(texture)
	{}

MGDTexture* GameObject::GetTexture()
{
	return this->texture;
}

/*
void GameObject::SetTexture(MGDTexture* texture)
{
	this->texture = texture;
}
*/

bool GameObject::IsEnabled()
{
	return this->enabled;
}

void GameObject::Enable()
{
	this->enabled = true;
}

void GameObject::Disable()
{
	this->enabled = false;
}

GamePrefab::GamePrefab() {}

GamePrefab::GamePrefab(MGDTexture texture)
{
	this->textures.Add(texture);
	this->texture = &this->textures[0];
}

void GamePrefab::AddTexture(MGDTexture texture)
{
	this->textures.Add(texture);
}

MGDTexture* GamePrefab::GetTexture()
{
	return this->texture;
}

GameRectangle::GameRectangle()
	: GameObject()
	{}

GameRectangle::GameRectangle(vec2f position, MGDTexture* texture, unsigned int width, unsigned int height)
	: GameObject(position, texture)
	, width(width)
	, height(height)
	{}

void GameRectangle::Render()
{
	// TODO
}

GameRectanglePrefab::GameRectanglePrefab()
	: GamePrefab()
	{}

GameRectanglePrefab::GameRectanglePrefab(MGDTexture texture, unsigned int width, unsigned int height)
	: GamePrefab(texture)
	, width(width)
	, height(height)
	{}

GameWall::GameWall()
	: GameRectangle()
	{}

GameWall::GameWall(vec2f position, MGDTexture* texture, unsigned int width, unsigned int height, unsigned int maxHitCount)
	: GameRectangle(position, texture, width, height)
	, hitCount(maxHitCount)
{
	this->textures = List<MGDTexture*>();
}

/*
void GameWall::AddTexture(unsigned int atHitCount, MGDTexture* texture)
{
	unsigned int diff = this->textures.GetSize() - atHitCount;
	
	if (diff <= 0)
	{
		for (int i = diff; i <= 0; --i)
			this->textures.Add(nullptr);

		this->textures.Add(texture);

		return;
	}

	this->textures.Insert(texture, atHitCount);
}
*/

unsigned int GameWall::GetHitCount()
{
	return this->hitCount;
}

GameWallPrefab::GameWallPrefab()
	: GameRectanglePrefab()
	{}

GameWallPrefab::GameWallPrefab(MGDTexture texture, unsigned int width, unsigned int height, unsigned int maxHitCount)
	: GameRectanglePrefab(texture, width, height)
	, maxHitCount(maxHitCount)
	{}

GameBall::GameBall()
	: GameObject()
	{}

GameBall::GameBall(vec2f position, MGDTexture* texture, unsigned int size, float speed)
	: GameObject(position, texture)
	, size(size)
	, speed(speed)
	{} // velocity(vec2f()) is called by default when allocating velocity memory

vec2f GameBall::GetVelocity()
{
	return this->velocity;
}

void GameBall::Render()
{
	// TODO
}

GameBallPrefab::GameBallPrefab()
	: GamePrefab()
	{}

GameBallPrefab::GameBallPrefab(MGDTexture texture, unsigned int size, float speed)
	: GamePrefab(texture)
	, size(size)
	, speed(speed)
	{}
