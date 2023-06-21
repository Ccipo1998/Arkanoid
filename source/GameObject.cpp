
#include "GameObject.h"
#include "Singleton.hpp"
#include "GameManager.h"
#include "ArkanoidPhysics.h"
#include "ArkanoidMath.h"

GameObject::GameObject()
	: enabled(true)
	{}

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

void GamePrefab::AddTexture(MGDTexture* texture)
{
	if (this->textures.GetSize() == 0)
		this->texIndex = 0;

	this->textures.Add(texture);
}

MGDTexture* GamePrefab::GetTexture()
{
	if (this->textures.GetSize() == 0)
		return nullptr;
		
	return this->textures[this->texIndex];
}

void GamePrefab::SetTexture(unsigned int index)
{
	if (index < this->textures.GetSize())
		this->texIndex = index;
}

GamePrefab::~GamePrefab()
{
	// the lists free their memory and the memory of the object contained by themselves
}

GameRect::GameRect()
	: GameObject()
	, prefab(nullptr)
	{}

GameRect::GameRect(vec2f position, float width, float height, GamePrefab* prefab)
	: GameObject()
	, position(position)
	, width(width)
	, height(height)
	, prefab(prefab)
	{}

void GameRect::Render()
{
	if (!this->enabled)
		return;

	// check if the game rect has a valid prefab to use
	if (this->prefab == nullptr || this->prefab->GetTexture() == nullptr)
		return;

	// create temp sdl rect
	SDL_Rect rect = { this->position.x, this->position.y, this->width, this->height };
	
	// render current texture
	this->prefab->GetTexture()->renderCopyEx(&rect);
}

GamePrefab* GameRect::GetPrefab()
{
	return this->prefab;
}

void GameRect::Update(double deltaTime)
{
	if (!this->enabled)
		return;
	
	// TODO
}

GameRect::~GameRect()
{
	// here we dont delete the prefab pointer, because a prefab does not depend on the gameobject using it
}

GameWallPrefab::GameWallPrefab()
	: GamePrefab()
	{}

GameWallPrefab::GameWallPrefab(unsigned int maxHitCount)
	: maxHitCount(maxHitCount)
	{}

void GameWallPrefab::SetMaxHitCount(unsigned int maxHitCount)
{
	this->maxHitCount = maxHitCount;
}

unsigned int GameWallPrefab::GetMaxHitCount()
{
	return this->maxHitCount;
}

GameWall::GameWall()
	: GameRect()
	{}

GameWall::GameWall(vec2f position, float width, float height, GameWallPrefab* prefab)
	: GameRect(position, width, height, prefab)
{
	if (prefab != nullptr)
		this->hitCount = prefab->GetMaxHitCount();
}

unsigned int GameWall::GetHitCount()
{
	return this->hitCount;
}

void GameWall::Hit()
{
	--this->hitCount;
}

void GameWall::Update(double deltaTime)
{
	if (!this->enabled)
		return;

	if (this->hitCount == 0)
		this->Disable();
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

GameBall::GameBall()
	: GameRect()
	{} // velocity(vec2f()) is called by default when allocating velocity memory

GameBall::GameBall(vec2f position, float size, GamePrefab* prefab, float speed)
	: GameRect(position, size, size, prefab)
	, speed(speed)
	{}

vec2f GameBall::GetDirection()
{
	return this->direction;
}

void GameBall::SetDirection(vec2f newDirection)
{
	this->direction = amath::normalize(newDirection);
}

void GameBall::Launch()
{
	this->direction = vec2f(.5f, -.5f);
}

void GameBall::Update(double deltaTime)
{
	// only if the game ball is enabled
	if (!this->enabled)
		return;

	// position update
	this->position += this->direction * this->speed * deltaTime;
}

GamePlatform::GamePlatform(vec2f position, float width, float height, GamePrefab* prefab)
	: GameRect(position, width, height, prefab)
	, velocity(position)
	, inputReceived(false)
	{}

void GamePlatform::HandleEvent(SDL_Event& sdlEvent)
{
	// platform motion
	if (sdlEvent.type == SDL_MOUSEMOTION)
	{
		// new position
		vec2f newPos = vec2f(sdlEvent.motion.x - (this->width / 2.0f), this->position.y);

		// update velocity
		this->velocity = newPos - this->position;

		this->inputReceived = true;
	}
}

vec2f GamePlatform::GetVelocity()
{
	return this->velocity;
}

void GamePlatform::Update(double deltaTime)
{
	if (!this->enabled)
		return;

	if (!this->inputReceived)
	{
		this->velocity = vec2f();

		return;
	}

	this->position += this->velocity;
	this->inputReceived = false;
}
