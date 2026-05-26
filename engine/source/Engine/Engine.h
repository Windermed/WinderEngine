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
	RenderWindow& GetWindow() { return Window; };

	/* Allows us to access our engine globally. */
	static Engine* GetEngine() { return EngineInstance; }

	/* Returns our Player object. */
	Player& GetPlayer();

	float GetDeltaTime() const { return DeltaT; }

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

protected:

	/* Private functions for internal use only */
	virtual void Input();
	virtual void Update(float DeltaTime);
	virtual void Draw();

	/* engine's version of GetName since it doesn't inherit from Object */
	virtual const char* GetName() const { return "Engine"; }

private:

	/* DELTA TIME */
	float DeltaT = 0.0f;

protected:
	
	// using this from my other project.
	static Engine* EngineInstance; // static pointer to the engine.

	/* GameMode Engine */
	GameMode GameMode = GameMode::Menu;
	GameState GameState = GameState::Playing;
	

	/* A regular RenderWindow */
	RenderWindow Window;

	/* player object */
	Player* CurrentPlayer;

	/* Input */
	Keyboard::Key LastKeyPressed = Keyboard::Key::Unknown;

	

};