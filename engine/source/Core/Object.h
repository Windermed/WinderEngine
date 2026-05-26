#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
using namespace sf;

// this is the base class for all of our game objects.
class Object
{
public:
	virtual ~Object() {};

	// core loop
	virtual void Update(float DeltaTime) = 0;
	virtual void Draw(RenderWindow& window) = 0;

	virtual bool IsOffScreen() const { return false; }
	virtual float GetTTL() const { return 1.0f; }
	virtual bool IsAlive() const { return GetTTL() > 0.0f && !IsOffScreen(); }

	virtual const char* GetName() const { return "Object"; }

	// position
	virtual Vector2f GetPosition() const { return Position; }
	virtual void SetPosition(Vector2f pos) { Position = pos; }

	void SetShowCollision(bool show) { bShowCollision = show; }
	bool IsShowingCollision() const { return bShowCollision; }

protected:
	Vector2f Position;
	bool bShowCollision = false;
};

