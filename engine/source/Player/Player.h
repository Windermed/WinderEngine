#pragma once
#include "Object.h"
#include "Textures/GameSprite.h"
#include "Character/Character.h"
#include "Animation/Animator.h"
#include <vector>

using namespace sf;
using namespace std;

class Engine;

// using code from my own project as a base.
class Player : public Character
{
public:
	Player();

	// object overrides
	void Update(float DeltaTime) override;
	void Draw(RenderWindow& window) override;
	const char* GetName() const override { return "Player"; }
	
	// character overrides
	GameSprite& GetSprite() override { return CharacterSprite; }

	// input lock. can disable player input when needed
	void SetInputLocked(bool locked) { bIsInputLocked = locked; }
	bool IsInputLocked() const { return bIsInputLocked; }

	void SetMovementBounds(float minX, float minY, float maxX, float maxY)
	{
		BoundsMinX = minX;
		BoundsMinY = minY;
		BoundsMaxX = maxX;
		BoundsMaxY = maxY;
	}

protected:
	virtual void HandleInput(float dt);

protected:
	Animator PlayerAnimator;

	bool bIsInputLocked = false;

	float BoundsMinX = 0.0f;
	float BoundsMinY = 0.0f;
	float BoundsMaxX = (float)SCREEN_WIDTH;
	float BoundsMaxY = (float)SCREEN_HEIGHT;
};

