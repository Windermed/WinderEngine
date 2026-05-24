#pragma once
#include "Object.h"
#include "Textures/GameSprite.h"
#include <vector>

using namespace sf;
using namespace std;

class Engine;

// using code from my own project as a base.
class Character : public Object
{
public:
	Character();

	// object overrides
	void Update(float dt) override;
	void Draw(RenderWindow& window) override;
	bool IsOffScreen() const override { return false; }
	const char* GetName() const override { return "Character"; }

	// position.
	void ResetPosition();

	// sprite
	GameSprite& GetSprite() { return PlayerSprite;  }
	void SetSprite(const string& path) { PlayerSprite.Load(path); }

	// movement
	void SetSpeed(float newSpeed) { Speed = newSpeed; }
	float GetSpeed() const { return Speed; }

	// visibility
	void SetVisible(bool visible) { bIsVisible = visible; }
	bool IsVisible() const { return bIsVisible; }

protected:
	void HandleInput(float dt);

protected:

	// sprites 
	GameSprite PlayerSprite;
	float Speed = 420.0f;
	bool bIsVisible = true;
};

