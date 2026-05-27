#include <iostream>
#include "StatBar.h"
#include "GameText.h"

float StatBar::UIScale = 1.0f;
float StatBar::LabelFontScale = 1.0f;

StatBar::StatBar(const std::string& label, int value, int maxValue, Vector2f position)
{
	Label = label;
	Value = value;
	MaxValue = MAX_STAT_VALUE;
	Position = position;

	LabelText = GameText(label, (unsigned int)(16.f * UIScale * LabelFontScale), Color::White, false);
	ValueText = GameText("(" + std::to_string(value) + ")", (unsigned int)(16.f * UIScale * LabelFontScale), Color::White, false);

	PointTexture.loadFromFile("content/textures/ui/spr_statbar_point.png");
	EmptyPointTexture.loadFromFile("content/textures/ui/spr_statbar_empty.png");

	// disable smoothing so pixels stay crisp
	PointTexture.setSmooth(false);
	EmptyPointTexture.setSmooth(false);

	SetPosition(position);
}

void StatBar::SetPosition(Vector2f position)
{
	Position = position;

	// offset for label. adjust if needed.
	float LabelOffset = 90.0f * UIScale;

	// offset for value. adjust if needed.
	float ValueOffset = 40.0f * UIScale;

	// offset for bar. adjust if needed.
	float BarOffset = 70.0f * UIScale;

	LabelText.setPosition({ position.x, position.y });
	ValueText.setPosition({ position.x + ValueOffset, position.y });
	BarStartX = position.x + BarOffset;

}

void StatBar::Draw(RenderWindow& window)
{
	
	//Message("BarStartX: " << BarStartX << " TileScale: " << UIScale << " MaxValue: " << MaxValue);

	ValueText.setString("(" + std::to_string(Value) + ")");
	LabelText.DrawText();

	float StartX = Position.x + 110.0f;
	float ScaledW = TileW * UIScale;
	float TileStep = ScaledW + TileGap;

	Message("MaxValue is: " << MAX_STAT_VALUE);
	// go until the max value of stat points
	for (int i = 0; i < MaxValue; i++)
	{
		Sprite tile(i < Value ? PointTexture : EmptyPointTexture);

		if (i < Value)
		{
			tile.setColor(FillColor);
		}
		tile.setScale({ UIScale, UIScale });
		tile.setPosition({ BarStartX + i * TileStep, Position.y });
		window.draw(tile);
	}

	ValueText.DrawText();
}
