#include "Character.h"
#include "Engine.h"
#include "Sounds/SoundManager.h"

Character::Character()
{
	Position = Vector2f(960.0f, 540.0f);
	PlayerSprite = GameSprite("content/textures/spr_placeholder.png", Position);
	PlayerSprite.setPosition(Position);
}

void Character::ResetPosition()
{
	Position = Vector2f(960.0f, 540.0f);
	PlayerSprite.setPosition(Position);
}

void Character::HandleInput(float dt)
{

}

void Character::Update(float dt)
{
	HandleInput(dt);
	PlayerSprite.setPosition(Position);
}

void Character::Draw(RenderWindow& window)
{
	if (bIsVisible)
		window.draw(PlayerSprite);
}