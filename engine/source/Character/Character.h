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
	void Update(float DeltaTime) override;
	void Draw(RenderWindow& window) override;
	bool IsOffScreen() const override { return false; }
	const char* GetName() const override { return "Character"; }

	FloatRect GetBounds() const override
	{
		FloatRect Full = CharacterSprite.getGlobalBounds();
		float CollisionHeight = Full.size.y * 0.32f;
		return FloatRect({ Full.position.x, Full.position.y + Full.size.y - CollisionHeight }, { Full.size.x, CollisionHeight });
	}
	// position.
	void ResetPosition();

	// sprite
	virtual GameSprite& GetSprite() { return CharacterSprite;  }
	void SetSprite(const string& path) { CharacterSprite.Load(path); }

	// movement
	void SetSpeed(float newSpeed) { Speed = newSpeed; }
	float GetSpeed() const { return Speed; }

	// visibility
	void SetVisible(bool visible) { bIsVisible = visible; }
	bool IsVisible() const { return bIsVisible; }

	// player direction.
	string GetFacingDirection() const { return LastFacingDirection; }

protected:
	void HandleInput(float dt);

protected:

	// sprites 
	GameSprite CharacterSprite;
	float Speed = 420.0f;
	bool bIsVisible = true;

	// direction

	std::string LastFacingDirection = "Down";
};

