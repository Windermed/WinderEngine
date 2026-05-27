#pragma once
#include <string>

// an interactable interface that's meant to be used for any objects that you may want the player
// to interact with.
class Interactable
{
public:
	virtual ~Interactable() {}

	virtual void OnInteract() {}

	bool CanInteract() const { return bCanInteract; };
	void SetInteract(bool interactable) { bCanInteract = interactable; }

protected:
	bool bCanInteract = false;
};