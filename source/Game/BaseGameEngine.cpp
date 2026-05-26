#include "BaseGameEngine.h"
#include "Sounds/SoundManager.h"



void BaseGameEngine::Initialize()
{
	// center our placeholder sprite.
	DemoSprite = GameSprite("content/textures/spr_placeholder.png");
	DemoSprite.SetCenterPosition({ 0, 100 });
	DemoSprite.SetScale(3.0f);

	// title text with rainbow effect.
	TitleText = GameText("WinderEngine", 96, Color::White, false);
	TitleText.CenterAtY(-150.0f);
	TitleText.SetRainbowEffect(true);

	// setup teaser text
	TeaserText = GameText("With more to come soon!", 32, Color::Yellow, false);
	TeaserText.CenterAtY(-90.0f);

	// subtitle
	SubtitleText = GameText("A lightweight C++ engine built using SFML 3.1", 32, Color(200, 200, 200, 255), false);
	SubtitleText.CenterAtY(-50.0f);
}

void BaseGameEngine::Input()
{
	// call base input.
	Engine::Input();
}

void BaseGameEngine::Update(float DeltaTime)
{
	Engine::Update(DeltaTime);

	RotationAngle += 90.0f * DeltaTime;
	if (RotationAngle >= 360.0f)
	{
		RotationAngle -= 360.0f;
	}

	DemoSprite.setRotation(degrees(RotationAngle));

}

void BaseGameEngine::Draw()
{
	Window.clear(Color(20, 20, 30));

	TitleText.DrawText();
	TeaserText.DrawText();
	SubtitleText.DrawText();

	DemoSprite.DrawSprite();

	Window.display();
}