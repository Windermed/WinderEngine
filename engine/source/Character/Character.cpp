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

void Character::StartHitEffect()
{
	bFlashing = true;
	FlashTimer = 0.0f;
	FlashTickTimer = 0.0f;
	bFlashVisible = true;

	bShaking = true;
	ShakeTimer = 0.0f;
	ShakeBasePosition = Position;
}

void Character::UpdateHitEffect(float DeltaTime)
{
	// if our character is flashing.
	if (bFlashing)
	{
		FlashTimer += DeltaTime;
		FlashTickTimer += DeltaTime;

		if (FlashTickTimer >= flashRate)
		{
			FlashTickTimer = 0.0f;
			bFlashVisible = !bFlashVisible;

			// alternate between a white tint
			CharacterSprite.setColor(bFlashVisible ? Color::White : GetBaseColor());

		}

		if (FlashTimer >= FlashDuration)
		{
			bFlashing = false;
			bFlashVisible = true;
			CharacterSprite.setColor(GetBaseColor());
		}
	}

	// shake
	if (bShaking)
	{
		ShakeTimer += DeltaTime;

		if (ShakeTimer >= ShakeDuration)
		{
			bShaking = false;
			CharacterSprite.setPosition(Position);
		}
		else
		{
			float offset = std::sin(ShakeTimer * 80.f) * ShakeMagnitude;
			CharacterSprite.setPosition({ Position.x + offset, Position.y });
		}
	}

}

void Character::HandleInput(float dt)
{

}

void Character::Update(float DeltaTime)
{
	UpdateHitEffect(DeltaTime);
	HandleInput(DeltaTime);
	if (!bShaking)
	{
		CharacterSprite.setPosition(Position);
	}
}

void Character::Draw(RenderWindow& window)
{
	if (bIsVisible)
		window.draw(CharacterSprite);
}