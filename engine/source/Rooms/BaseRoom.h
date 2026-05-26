#pragma once
#include "Object.h"
#include "Textures/GameSprite.h"

using namespace sf;

class BaseRoom : public Object
{
public:
	BaseRoom(const std::string& spritePath);

	void Update(float dt) override {}
	void Draw(sf::RenderWindow& window) override;
	const char* GetName() const override { return "BaseRoom"; }

	Vector2f GetRoomSize() const;
private:
	GameSprite RoomSprite;
};