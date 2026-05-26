#pragma once
#include "Engine/Engine.h"

// base game engine class - this should be renamed and used for your own project.
class BaseGameEngine : public Engine
{
public:
	BaseGameEngine() {}

	// initialize the engine instance.
	static void Init()
	{
		if (!EngineInstance)
		{
			EngineInstance = new BaseGameEngine();

			// initialize after the instance is set.
			static_cast<BaseGameEngine*>(EngineInstance)->Initialize();
		}
	}

protected:

	/* replacement for the default constructor. just call this on Init() */
	void Initialize();

	void Input() override;
	void Update(float DeltaTime) override;
	void Draw() override;

	const char* GetName() const override { return "BaseGameEngine"; }

private:
	// demo sprites
	GameSprite DemoSprite;
	float RotationAngle = 0.0f;

	// demo text.
	GameText TitleText;
	GameText SubtitleText;
	GameText TeaserText;

};