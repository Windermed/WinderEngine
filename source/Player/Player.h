#pragma once
#include "Object.h"
#include "Textures/GameSprite.h"
#include "Character/Character.h"
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
	void Update(float dt) override;
	void Draw(RenderWindow& window) override;
	const char* GetName() const override { return "Player"; }

	// input lock. can disable player input when needed
	void SetInputLocked(bool locked) { bIsInputLocked = locked; }
	bool IsInputLocked() const { return bIsInputLocked; }

protected:
	virtual void HandleInput(float dt);

protected:
	bool bIsInputLocked = false;
};

