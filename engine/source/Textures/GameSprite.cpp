#include "GameSprite.h"
#include "Engine/Engine.h"

void GameSprite::DrawSprite()
{
	Engine::GetEngine()->GetWindow().draw(*this);
}