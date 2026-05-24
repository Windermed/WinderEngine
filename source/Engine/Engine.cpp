#include "Engine.h"
#include <fstream>
#include "Player/Player.h"
#include "Sounds/SoundManager.h"


// because the compiler needs it.
Engine* Engine::EngineInstance = nullptr;

Engine::Engine()
{

	Image icon;
	float titleY = SCREEN_HEIGHT / 2.0f - 200.0f;
	float subtitleY = SCREEN_HEIGHT / 2.0f - 100.0f;

	// start seeding
	srand(static_cast<unsigned int>(time(nullptr)));

	// locking it to 1080p as its annoying to work on a widescreen monitor.
	m_Window.create(VideoMode({ (unsigned int)SCREEN_WIDTH, (unsigned int)SCREEN_HEIGHT }), "BaseGame", Style::Default);
	m_Player = new Player(); // we will need to use a pointer for our player.

	if (icon.loadFromFile(ICON_PATH))
	{
		m_Window.setIcon(icon.getSize(), icon.getPixelsPtr());
	}

	//m_activeSpawner->SetInfinite(true);

	SoundManager::GetInstance();
}

void Engine::Run()
{

	Clock clock; // initializing clock.

	Message("Engine will now boot!")

	while (m_Window.isOpen())
	{
		Time elapsed = clock.restart();
		float dtAsSeconds = elapsed.asSeconds();

		this->Input();
		this->Update(dtAsSeconds);
		this->Draw();
	}

}

Player& Engine::GetPlayer()
{
	return *m_Player; // since we are using the ACTUAL player, we need to return a reference and not a copy.
}

void Engine::Input()
{
	// sf event no longer uses a default constructor in 3.1 so we will do something else instead.

	// INPUTS.
	while (const auto event = m_Window.pollEvent())
	{
		if (event->is<Event::Closed>())
			m_Window.close();
	}

	if (Mouse::isButtonPressed(Mouse::Button::Left)) // allows for multiple particles to be spawned as you hold left.
	{
	

	}
}

// Engine Update.
void Engine::Update(float dtAsSeconds)
{
	// EXPERIMENTAL.
	m_dt = dtAsSeconds;
}


void Engine::Draw()
{
	m_Window.clear();



	m_Window.display();
}
