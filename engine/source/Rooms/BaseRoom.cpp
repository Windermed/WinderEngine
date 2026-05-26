#include "BaseRoom.h"

BaseRoom::BaseRoom(const std::string& spritePath)
{
	RoomSprite.Load(spritePath);

	// position at top left.
	RoomSprite.setOrigin({ 0, 0 });
	RoomSprite.setPosition({ 0, 0 });
}

void BaseRoom::Draw(sf::RenderWindow& window)
{
	window.draw(RoomSprite);
}

Vector2f BaseRoom::GetRoomSize() const
{
	return RoomSprite.GetSize();
}