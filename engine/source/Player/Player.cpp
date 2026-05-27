#include "Player.h"
#include "Engine.h"
#include "Sounds/SoundManager.h"

Player::Player()
{
	Position = Vector2f(960.0f, 540.0f);
	CharacterSprite = GameSprite("content/textures/player/character_base_16x16_temp.png", Position);
	CharacterSprite.setPosition(Position);
	CharacterSprite.SetScale(6);
	CharacterSprite.setTextureRect(IntRect({ 0, 0 }, { 16, 16 }));
	CharacterSprite.setOrigin({ 8.0f, 8.0f });
	// assuming we use 16x16 sprites, we go 4 frames per direction.

	AnimationClip WalkUp; // this took way too long than i thought.
	WalkUp.FrameRate = 8.0f;
	WalkUp.Frames = {
		IntRect({0, 16}, {16, 16}),
		IntRect({16, 16}, {16, 16}),
		IntRect({32, 16}, {16, 16}),
		IntRect({48, 16}, {16, 16})
	};

	AnimationClip WalkDown;
	WalkDown.FrameRate = 8.0f;
	WalkDown.Frames = {
		IntRect({0, 0}, {16, 16}),
		IntRect({16, 0}, {16, 16}),
		IntRect({32, 0}, {16, 16}),
		IntRect({48, 0}, {16, 16})
	};

	AnimationClip WalkLeft;
	WalkLeft.FrameRate = 8.0f;
	WalkLeft.Frames = {
		IntRect({0, 48}, {16, 16}),
		IntRect({16, 48}, {16, 16}),
		IntRect({32, 48}, {16, 16}),
		IntRect({48, 48}, {16, 16})
	};
	

	AnimationClip WalkRight;
	WalkRight.FrameRate = 8.0f;
	WalkRight.Frames = {
		IntRect({0, 32}, {16, 16}),
		IntRect({16, 32}, {16, 16}),
		IntRect({32, 32}, {16, 16}),
		IntRect({48, 32}, {16, 16})
	};

	// Idle clips which are just the first frame of each direction
	AnimationClip IdleDown;
	IdleDown.FrameRate = 1.0f;
	IdleDown.Frames = { IntRect({0, 0}, {16, 16}) };

	AnimationClip IdleUp;
	IdleUp.FrameRate = 1.0f;
	IdleUp.Frames = { IntRect({0, 16}, {16, 16}) };

	AnimationClip IdleLeft;
	IdleLeft.FrameRate = 1.0f;
	IdleLeft.Frames = { IntRect({0, 48}, {16, 16}) };

	AnimationClip IdleRight;
	IdleRight.FrameRate = 1.0f;
	IdleRight.Frames = { IntRect({0, 32}, {16, 16}) };

	PlayerAnimator.AddClip("WalkUp", WalkUp);
	PlayerAnimator.AddClip("WalkDown", WalkDown);
	PlayerAnimator.AddClip("WalkLeft", WalkLeft);
	PlayerAnimator.AddClip("WalkRight", WalkRight);

	PlayerAnimator.AddClip("IdleUp", IdleUp);
	PlayerAnimator.AddClip("IdleDown", IdleDown);
	PlayerAnimator.AddClip("IdleLeft", IdleLeft);
	PlayerAnimator.AddClip("IdleRight", IdleRight);

	PlayerAnimator.Play("WalkDown");

}

void Player::HandleInput(float dt)
{
	if (bIsInputLocked) return;

	Vector2f Dir(0.0f, 0.0f);
	bool bIsMoving = false;

	// movement.
	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		Dir.y -= 1.0f;
		bIsMoving = true;
		LastFacingDirection = "Up";
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		Dir.y += 1.0f;
		bIsMoving = true;
		LastFacingDirection = "Down";
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		Dir.x -= 1.0f;
		bIsMoving = true;
		LastFacingDirection = "Left";
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		Dir.x += 1.0f;
		bIsMoving = true;
		LastFacingDirection = "Right";
	}

	// play the idle anim within the last direction when the player is not moving
	if (bIsMoving)
		PlayerAnimator.Play("Walk" + LastFacingDirection);
	else
		PlayerAnimator.Play("Idle" + LastFacingDirection);

	// normalize diagonal movement
	if (Dir.x != 0.0f && Dir.y != 0.0f)
		Dir /= sqrt(2.0f);

	Position += Dir * Speed * dt;

	Position.x = std::max(BoundsMinX, std::min(BoundsMaxX, Position.x));
	Position.y = std::max(BoundsMinY, std::min(BoundsMaxY, Position.y));
}

void Player::Update(float DeltaTime)
{
	// update the animator
	PlayerAnimator.Update(DeltaTime);

	// apply curernt frame to sprite
	CharacterSprite.setTextureRect(PlayerAnimator.GetCurrentFrame());

	HandleInput(DeltaTime);
	CharacterSprite.setPosition(Position);
}

void Player::Draw(RenderWindow& window)
{
	if (bIsVisible)
		window.draw(CharacterSprite);
}