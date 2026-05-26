#include "Engine.h"
#include <fstream>
#include "Player/Player.h"
#include "Sounds/SoundManager.h"


// because the compiler needs it.
Engine* Engine::EngineInstance = nullptr;

Engine::Engine()
{
	Image icon;
	string iconToLoad = "";

	float titleY = SCREEN_HEIGHT / 2.0f - 200.0f;
	float subtitleY = SCREEN_HEIGHT / 2.0f - 100.0f;

	// start seeding
	srand(static_cast<unsigned int>(time(nullptr)));

	// locking it to 1080p as its annoying to work on a widescreen monitor.
	Window.create(VideoMode({ (unsigned int)SCREEN_WIDTH, (unsigned int)SCREEN_HEIGHT }), "BaseGame", Style::Default);
	this->CurrentPlayer = new Player(); // we will need to use a pointer for our player.

#ifdef NDEBUG
	iconToLoad = ICON_PATH; // release build icon.
#else
	iconToLoad = ICON_DEBUG_PATH; // debug build icon.
#endif

	// load up the icon depending on target.
	if (icon.loadFromFile(iconToLoad))
	{
		Window.setIcon(icon.getSize(), icon.getPixelsPtr());
	}

	SoundManager::GetInstance();
}

void Engine::Run()
{
	Clock clock; // initializing clock.
	Message("Engine will now boot!")

	while (Window.isOpen())
	{
		Time elapsed = clock.restart();
		float DeltaTime = elapsed.asSeconds();

		this->Input();
		this->Update(DeltaTime);
		this->Draw();
	}
}

Player& Engine::GetPlayer()
{
	return *CurrentPlayer; // since we are using the ACTUAL player, we need to return a reference and not a copy.
}

void Engine::Input()
{
	// sf event no longer uses a default constructor in 3.1 so we will do something else instead.

	// INPUTS.
	while (const auto event = Window.pollEvent())
	{
		if (event->is<Event::Closed>())
			Window.close();

		if (const auto* keyEvent = event->getIf<Event::KeyPressed>())
		{
			LastKeyPressed = keyEvent->code;
		}
	}
}

// Engine Update.
void Engine::Update(float DeltaTime)
{
	// EXPERIMENTAL.
	this->DeltaT = DeltaTime;
}


void Engine::Draw()
{
	Window.clear();
	Window.display();
}
