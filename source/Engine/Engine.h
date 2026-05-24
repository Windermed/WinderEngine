#pragma once
#include <SFML/Graphics.hpp>
#include "Core/Constants.h"
#include "UI/GameText.h"
#include "Player/Player.h"

using namespace sf;
using namespace std;

enum class GameMode
{
	Menu = 0,
	Particles = 1,
	BulletHell = 2
};

enum class GameState
{
	Win = 0,
	GameOver = 1,
	Playing = 2,
	None = 3
};

// we should make seperate classes in the future to not clutter up Engine.
class Engine
{
public:

	/* Main Engine Constructor */
	Engine();

	/* Run func that will call all the private functions */
	void Run();

	/* Getter of Current Window */
	RenderWindow& GetWindow() { return m_Window; };

	/* Allows us to access our engine globally. */
	static Engine* GetEngine() { return EngineInstance; }

	/* Returns our Player object. */
	Player& GetPlayer();

	/* Initializes the Engine instance. */
	static void Init()
	{
		if (!EngineInstance)
		{
			EngineInstance = new Engine;
		}
	}

	/* Deletes engine. */
	static void Shutdown()
	{
		delete EngineInstance;
		EngineInstance = nullptr;
	}
	
	template<typename T>
	void CleanupVector(vector<T>& vec, float dt)
	{
		// just so that we aren't inheriting objects that aren't from the Object class.
		static_assert(is_base_of<Object, T>::value, "T must inherit from Object");
		
		auto it = vec.begin();
		while (it != vec.end())
		{
			if (it->IsAlive())
			{
				it->Update(dt);
				++it;
			}
			else
			{
				it = vec.erase(it);
			}
		}
	}

private:

	/* Private functions for internal use only */
	void Input();
	void Update(float dtAsSeconds);
	void Draw();

private:
	
	// using this from my other project.
	static Engine* EngineInstance; // static pointer to the engine.

	/* GameMode Engine */
	GameMode m_gameMode = GameMode::Menu;
	GameState m_GameState = GameState::Playing;
	

	/* A regular RenderWindow */
	RenderWindow m_Window;

	/* player object */
	Player* m_Player;

	/* DELTA TIME */
	float m_dt = 0.0f;


	/* Input */
	Keyboard::Key m_lastKeyPressed = Keyboard::Key::Unknown;

	

};