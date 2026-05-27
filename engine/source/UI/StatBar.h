#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "UI/GameText.h"

using namespace sf;
using namespace std;

// a stat bar class. useful for displaying progress.
class StatBar
{
public:

	// @param label - this is the stat name (so something like STR)
	// @param value - this is the value you want to set the stat bar to. just set it below the max value.
	// @param maxValue - this is the maximum amount possible that the stat bar can support. can be configured if necessary.
	// @param position - this is the top-left position in our screen space.
	StatBar(const std::string& label, int value, int maxValue = MAX_STAT_VALUE, Vector2f position = { 0, 0 });

	// draws the statbar
	void Draw(RenderWindow& window);

	// updates the position of the bar.
	void SetPosition(Vector2f position);

	// updates the displayed stat value.
	void SetValue(int value) { Value = value; }

	// sets the tint color applied to the filled tile sprites.
	void SetColor(Color color) { FillColor = color; }

	// sets the scale of the tiles on the tile bar
	static void SetTileScale(float scale) { UIScale = scale; }

	// applies a different font for text such as STR and its value.
	void SetTextFont(const std::string& fontPath)
	{
		LabelText.SetFont(fontPath);
		ValueText.SetFont(fontPath);
	}

public:
	// the scale of the tile bar.
	static float UIScale;

	static float LabelFontScale;
private:
	// the stat label (e.g STR)
	string Label;

	// the current stat value
	int Value = 0;

	// the max stat value
	int MaxValue = 99;

	// the top-left screen position.
	Vector2f Position;

	// the tint color for filled tiles.
	Color FillColor = Color::White;

	// the x position where tiles begin.
	float BarStartX = 0.f;

	// the text for each stat name
	GameText LabelText;

	// the text for each stat value that displays next to the bar.
	GameText ValueText;

	// the filled tile sprite. it's white so that we can swap out colors.
	Texture PointTexture;

	// empty tile sprite.
	Texture EmptyPointTexture;

	// the tile dimensions that our sprite uses
	static const int TileW = 6;
	static const int TileH = 12;

	// the gap between each tile.
	static const int TileGap = 5;
};
