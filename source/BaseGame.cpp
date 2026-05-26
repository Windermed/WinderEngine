#include "Game/BaseGameEngine.h"

int main()
{
	// Gets a new instance of the engine directly and runs it.
	BaseGameEngine::Init();
	BaseGameEngine::GetEngine()->Run();
	BaseGameEngine::Shutdown();

	// Quit in the usual way when the engine is stopped
	return 0;
}