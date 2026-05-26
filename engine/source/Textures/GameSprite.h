#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Engine;

class GameSprite : public Sprite
{
public:
	// our default GameSprite constructor
	GameSprite() : Sprite(Texture)
	{
		//(void);
		Load("content/textures/spr_placeholder.png"); // loads a default sprite.
	}

	// copy constructor as sf::Texture doesn't copy well.
	GameSprite(const GameSprite& other) : Sprite(Texture)
	{
		FileName = other.FileName;
		bIsLoaded = other.bIsLoaded;
		
		// if sprite loads.
		if (bIsLoaded)
		{
			// reload textures
			Texture.loadFromFile(FileName);
			setTexture(Texture, true);
			CenterOrigin();

			// once reloaded, we preserve the OG transform.
			setPosition(other.getPosition());
			setScale(other.getScale());
			setRotation(sf::degrees(other.getRotation().asDegrees()));
		}
	}
	
	// a copy assignment op. we call this when an existing GameSprite is assigned from another.
	GameSprite& operator=(const GameSprite& other)
	{
		// avoid reloading if we assign to self.
		if (this != &other)
		{
			FileName = other.FileName;
			bIsLoaded = other.bIsLoaded;

			if (bIsLoaded)
			{
				// reload a texture so this instance can have it's own texture reference.
				Texture.loadFromFile(FileName);
				setTexture(Texture, true);
				CenterOrigin();

				// again, we will preserve the OG transform.
				setPosition(other.getPosition());
				setScale(other.getScale());
				setRotation(sf::degrees(other.getRotation().asDegrees()));
			}
		}
		return *this;
	}

	// constructor that loads from file.
	GameSprite(const string& filename) : Sprite(Texture) { Load(filename); }

	// load with position.
	GameSprite(const string& filename, Vector2f position) : Sprite(Texture)
	{
		Load(filename);
		setPosition(position);
	}

	GameSprite(const string& filename, Vector2f position, Vector2f scale) : Sprite(Texture)
	{
		Load(filename);
		setPosition(position);
		setScale(scale);
	}

	// load with position scale and rotation.
	GameSprite(const string& filename, Vector2f position, Vector2f scale, float rotation) : Sprite(Texture)
	{
		Load(filename);
		setPosition(position);
		setScale(scale);
		setRotation(sf::degrees(rotation));
	}

	// easily load textures from a file.
	bool Load(const string& filename)
	{
		FileName = filename;

		if (!Texture.loadFromFile(filename))
		{
			Message("ERROR: GameSprite has failed to load %s" << filename.c_str());
			Message("The Sprite is either invalid or NOT in directory.");
			bIsLoaded = false;
			return bIsLoaded;
		}

		setTexture(Texture, true);
		CenterOrigin();

		bIsLoaded = true;

		return bIsLoaded;
	}


	// reload sprite from the same file.
	bool Reload()
	{
		if (FileName.empty()) return false;
		return Load(FileName);
	}

	void DrawSprite();

	// center origin on the sprite's bounds
	void CenterOrigin()
	{
		FloatRect bounds = getLocalBounds();
		setOrigin({ bounds.size.x / 2.0f, bounds.size.y / 2.0f });
	}

	// allows us to flip horizontally
	void FlipX() { setScale({ -getScale().x, getScale().y }); }
	
	// flip vertically.
	void FlipY() { setScale({ getScale().x, -getScale().y }); }

	// set uniform scale
	void SetScale(float scale)  //made it take 1 scale for familiarity with other engines i've worked on.
	{
		setScale({ scale, scale });
	}

	// fade - 0 transparent, 255 opaque
	void SetOpacity(uint8_t opacity)
	{
		Color c = getColor();
		c.a = opacity;
		setColor(c);
	}

	// pulse opacity for effects we could do.
	void Pulse(float timer, uint8_t minOpacity = 80, uint8_t maxOpacity = 255)
	{
		float t = (sin(timer) + 1.0f) / 2.0f;
		uint8_t val = (uint8_t)(minOpacity + (maxOpacity - minOpacity) * t);
		SetOpacity(val);
	}

	// positions relative to screen center
	// positive moves right or down, negative will move left or up.
	void SetCenterPosition(Vector2f offset = { 0.0f, 0.0f })
	{
		setPosition({ (SCREEN_WIDTH / 2.0f) + offset.x, (SCREEN_HEIGHT / 2.0f) + offset.y });
	}

	// our getters
	bool IsLoaded() const { return bIsLoaded; }
	string GetFileName() const { return FileName; }

	Vector2f GetSize() const
	{
		FloatRect b = getLocalBounds();
		return Vector2f(b.size.x * getScale().x, b.size.y * getScale().y);
	}

private:
	Texture Texture;
	string FileName;
	bool bIsLoaded = false;


};