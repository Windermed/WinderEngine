#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class InteractProbe
{
public:
	void Spawn(Vector2f playerPos, FloatRect playerBounds, const std::string& currentFacingDirection)
	{
		float ProbeSize = 24.f;
		float W = playerBounds.size.x;
		float H = playerBounds.size.y;

		// spawns the probe depending on direction.
		if (currentFacingDirection == "Up")
		{
			Bounds = FloatRect({ playerPos.x - ProbeSize / 2.f, playerBounds.position.y - ProbeSize }, { ProbeSize, ProbeSize });
		}
		else if (currentFacingDirection == "Down")
		{
			Bounds = FloatRect({ playerPos.x - ProbeSize / 2.f, playerBounds.position.y + H }, { ProbeSize, ProbeSize });
		}
		else if (currentFacingDirection == "Left")
		{
			Bounds = FloatRect({ playerBounds.position.x - ProbeSize, playerPos.y - ProbeSize / 2.f }, { ProbeSize, ProbeSize });
		}
		else if (currentFacingDirection == "Right")
		{
			Bounds = FloatRect({ playerBounds.position.x + W, playerPos.y - ProbeSize / 2.f }, { ProbeSize, ProbeSize });
		}

		bIsActive = true;
		bUsedThisFrame = false;
	}

	void Clear() { bIsActive = false; }

	bool IsActive() const { return bIsActive; }
	FloatRect GetBounds() const { return Bounds; }

private:
	FloatRect Bounds;
	bool bIsActive = false;
	bool bUsedThisFrame = false;
};