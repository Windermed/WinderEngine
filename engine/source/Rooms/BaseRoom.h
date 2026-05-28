#pragma once
#include "Object.h"
#include "Textures/GameSprite.h"

using namespace sf;

class BaseRoom : public Object
{
public:
	BaseRoom(const std::string& spritePath, float scale = 1.0);

	void Update(float dt) override {}
	void Draw(sf::RenderWindow& window) override;
	const char* GetName() const override { return "BaseRoom"; }
public:


	// gets room size.
	Vector2f GetRoomSize() const;
	Vector2f GetRoomOffset() const { return RoomSprite.getPosition(); }
	Vector2f GetSpawnPoint() const { return PlayerSpawnPoint; }
	void SetSpawnPoint(Vector2f point) { PlayerSpawnPoint = point; }

	// temp solution until we look into doing a tile system.
	bool IsWalkable(Vector2f worldPos) const;
protected:
	GameSprite RoomSprite;
	Image RoomImage; 
	float RoomScale = 1.0f;

	Vector2f PlayerSpawnPoint = { 920, 540 };
};