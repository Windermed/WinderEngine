#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Constants.h"

using namespace sf; // so thats why 

class Engine; // forward declaration (or else circular dependency headaches again)


// a child class of SFML's Text with changes that make it easier to work with.
class GameText : public Text
{

public:

	// our default constructor for GameText.
	GameText::GameText() : Text(GetFont())
	{
		// default values for our game text.
		Init("Meet Potential Framework!", Vector2f(0, 0), 36, Color::White);
	}

	// if you want to set the text AND position.
	GameText::GameText(String text) : Text(GetFont())
	{
		Init(text, Vector2f(0, 0), 36, Color::White);
	}

	// text + position (on screen) constructor. useful if you want to set the text AND position.
	GameText::GameText(String text, Vector2f position) : Text(GetFont())
	{
		Init(text, position, 36, Color::White);
	}

	// text + position (screen) + text size constructor. useful if you want to do the same as above but configure the font size.
	GameText::GameText(String text, Vector2f position, unsigned int fontSize) : Text(GetFont())
	{
		Init(text, position, fontSize, Color::White);
	}

	// text + position (screen) + text size + text color constructor. useful if you want to do the same as above but configure the font size.
	GameText::GameText(String text, Vector2f position, unsigned int fontSize, Color color) : Text(GetFont())
	{
		Init(text, position, fontSize, color);
	}

	// text + font size, text color, text is centered ahh constructor. useful if you want to set text but want to disregard the position.
	GameText::GameText(String text, unsigned int fontSize, Color color, bool bIsTextCentered) : Text(GetFont())
	{
		Init(text, Vector2f(0, 0), fontSize, color);

		if (bIsTextCentered)
			CenterText(getLocalBounds());
	}

	// text + position (screen) + text size + text color + center text constructor. useful if you want to do the same as above but also center the text.
	GameText::GameText(String text, Vector2f position, unsigned int fontSize, Color color, bool bIsTextCentered) : Text(GetFont())
	{
		Init(text, position, fontSize, color);

		if (bIsTextCentered)
		{
			CenterText(this->getLocalBounds());
		}
	}

public:

	// get font
	static Font& GetFont()
	{
		if (!bIsFontLoaded)
		{
			if (!Font.openFromFile(FONT_PATH))
			{
				throw runtime_error("Font has failed to load!");
			}

			bIsFontLoaded = true;
		}
		return Font;
	}

	static Color HueToColor(float hue);

	// just to simply things.
	void DrawText();

	// center the text.
	void CenterText(FloatRect bounds);

	void FlashText(float flashRate = 0.5f)
	{
		bIsTextFlashing = true;
		bIsTextVisible = true;
		FlashRate = flashRate;
		FlashTimer = 0.0f;
		FlashDuration = -1.0f;
		ElapsedTime = 0.0f;
	}

	// Flash for a specified duration then stop.
	void FlashText(float duration, float flashRate = 0.5f)
	{
		bIsTextFlashing = true;
		bIsTextVisible = true;
		FlashRate = flashRate;
		FlashTimer = 0.0f;
		FlashDuration = duration;
		ElapsedTime = 0.0f;
	}

	// stops flashing text.
	void StopFlash()
	{
		bIsTextFlashing = false;
		bIsTextVisible = true;
		FlashTimer = 0.0f;
		ElapsedTime - 0.0f;
	}

	void UpdateFlash(float dt)
	{
		if (!bIsTextFlashing) return;

		FlashTimer += dt;
		ElapsedTime += dt;

		// toggle visibility on flash rate.
		if (FlashTimer > -FlashRate)
		{
			bIsTextVisible = !bIsTextVisible;
			FlashTimer = 0.0f;
		}

		// stop after specified duration if it's not infintite
		if (FlashDuration > 0.0f && ElapsedTime >= FlashDuration)
		{
			StopFlash();
		}
	}

	bool IsTextFlashing() const { return bIsTextFlashing; }

	// sets a rainbow wave color effect to text.
	void SetRainbowEffect(bool bEnabled)
	{
		bUseRainbowEffect = bEnabled;
		
		if (bEnabled)
		{
			RainbowClock.restart();
		}
		if (!bEnabled)
		{
			// if we've disabled this, we'll clear the preprocessor and restore the OG color.
			setGlyphPreProcessor(nullptr);
		}

	}

	bool IsRainbowEffect() const { return bUseRainbowEffect; }

	// Updates String and you can optionally re center it.
	//void SetText(String text, bool bRecenterText = false);
	
	// center horizontally and positions relative to screen center.
	// positive Y moves down, negative Y moves up.
	void CenterAtY(float offsetFromCenter)
	{
		FloatRect bounds = getLocalBounds();
		setOrigin({ bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f });
		setPosition({ SCREEN_WIDTH / 2.0f, (SCREEN_HEIGHT / 2.0f) + offsetFromCenter });
	}

private:

	void Init(String text, Vector2f position, unsigned int fontSize, Color color);

private:

	static Font Font;
	static bool bIsFontLoaded;

	bool bIsTextFlashing = false;
	bool bIsTextVisible = true;
	float FlashRate = 0.5f;
	float FlashTimer = 0.0f;

	// set to -1 for infinite.
	float FlashDuration = -1.0f;

	float ElapsedTime = 0.0f;

	// enable a rainbow effect to text.
	bool bUseRainbowEffect = false;

	// the rainbow timer.
	Clock RainbowClock;
};

