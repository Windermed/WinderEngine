#include "Character.h"
#include "Engine.h"
#include "Sounds/SoundManager.h"

Character::Character()
{
	Position = Vector2f(960.0f, 540.0f);
	CharacterSprite = GameSprite("content/textures/spr_placeholder.png", Position);
	CharacterSprite.setPosition(Position);
}

void Character::ResetPosition()
{
	Position = Vector2f(960.0f, 540.0f);
	CharacterSprite.setPosition(Position);
}

void Character::HandleInput(float dt)
{

}

void Character::Update(float DeltaTime)
{
	HandleInput(DeltaTime);
	CharacterSprite.setPosition(Position);
}

void Character::Draw(RenderWindow& window)
{
	if (bIsVisible)
		window.draw(CharacterSprite);
}