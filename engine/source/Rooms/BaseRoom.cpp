#include "BaseRoom.h"

BaseRoom::BaseRoom(const std::string& spritePath, float scale)
{

	RoomScale = scale;

	RoomSprite.Load(spritePath);
	RoomSprite.setOrigin({ 0, 0 });
	RoomSprite.setPosition({ 0, 0 });
	RoomSprite.SetScale(scale);

	// center the room sprite on screen
	Vector2f RoomSize = RoomSprite.GetSize();
	RoomSprite.setOrigin({ 0, 0 });
	RoomSprite.setPosition({(SCREEN_WIDTH / 2.0f) - (RoomSize.x / 2.0f), (SCREEN_HEIGHT / 2.0f) - (RoomSize.y / 2.0f)});

	// load image into memory for collision sampling.
	RoomImage.loadFromFile(spritePath);

	// default spawn point.
	PlayerSpawnPoint = Vector2f(RoomSprite.getPosition().x + RoomSize.x / 2.0, RoomSprite.getPosition().y + RoomSize.y / 2.0);


}

void BaseRoom::Draw(sf::RenderWindow& window)
{
	window.draw(RoomSprite);
}

Vector2f BaseRoom::GetRoomSize() const
{
	return RoomSprite.GetSize();
}

bool BaseRoom::IsWalkable(Vector2f worldPos) const
{
	Vector2f RoomOrigin = RoomSprite.getPosition();

	// conver tworld position to pixel coords
	int PixelX = (int)((worldPos.x - RoomOrigin.x) / RoomScale);
	int PixelY = (int)((worldPos.y - RoomOrigin.y) / RoomScale);

	// if we are outside of the room's bounds. it is not walkable.
	Vector2u ImageSize = RoomImage.getSize();
	if (PixelX < 0 || PixelY < 0 || PixelX >= (int)ImageSize.x || PixelY >= (int)ImageSize.y)
	{
		return false;
	}

	// then we sample the pixel.
	Color pixel = RoomImage.getPixel({ (unsigned int)PixelX, (unsigned int)PixelY });

	return pixel.r > 200 && pixel.g > 200 && pixel.b > 200;
}