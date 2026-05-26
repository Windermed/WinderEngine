#include "Player.h"
#include "Engine.h"
#include "Sounds/SoundManager.h"

Player::Player()
{
	Position = Vector2f(960.0f, 540.0f);
	PlayerSprite = GameSprite("content/textures/spr_placeholder.png", Position);
	PlayerSprite.setPosition(Position);
}

void Player::HandleInput(float dt)
{
	if (bIsInputLocked) return;

	Vector2f Dir(0.0f, 0.0f);


	if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
		Dir.y -= 1.0f;
	if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
		Dir.y += 1.0f;
	if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
		Dir.x -= 1.0f;
	if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
		Dir.x += 1.0f;

	// normalize diagonal movement
	if (Dir.x != 0.0f && Dir.y != 0.0f)
		Dir /= sqrt(2.0f);

	Position += Dir * Speed * dt;

	// clamp to screen bounds.
	Position.x = max(0.0f, min((float)SCREEN_WIDTH, Position.x));
	Position.y = max(0.0f, min((float)SCREEN_HEIGHT, Position.y));
}

void Player::Update(float DeltaTime)
{
	HandleInput(DeltaTime);
	PlayerSprite.setPosition(Position);
}

void Player::Draw(RenderWindow& window)
{
	if (bIsVisible)
		window.draw(PlayerSprite);
}