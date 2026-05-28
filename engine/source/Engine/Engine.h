#pragma once
#include <SFML/Graphics.hpp>
#include "Core/Constants.h"
#include "UI/GameText.h"
#include "Player/Player.h"

using namespace sf;
using namespace std;

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

	static void PlaySound(const std::string& fileName, float volume = 100.f);

protected:

	/* Private functions for internal use only */
	virtual void Input();
	virtual void Update(float DeltaTime);
	virtual void Draw();

	virtual void OnKeyPressed(Keyboard::Key key) {}

	/* engine's version of GetName since it doesn't inherit from Object */
	virtual const char* GetName() const { return "Engine"; }

	/* Draws the Collision. useful for debugging collision. */
	void DrawCollisionDebug();
	
	void RegisterObject(Object* obj) { RegisteredObjects.push_back(obj); }

	void UnregisterObject(Object* obj)
	{
		RegisteredObjects.erase(remove(RegisteredObjects.begin(), RegisteredObjects.end(), obj), RegisteredObjects.end());
	}

	/* allows you to delay before running another func. useful if you want to wait for something to happen. */
	void Delay(float seconds)
	{
		DelayDuration = seconds;
		DelayTimer = 0.f;
		bIsDelaying = true;

		// block until a delay is complete. but still process any other window events.
		Clock DelayClock;
		while (bIsDelaying)
		{
			DelayTimer += DelayClock.restart().asSeconds();
			if (DelayTimer >= DelayDuration)
			{
				bIsDelaying = false;
			}

			// in the meantime, keep other window events alive so that the game doesn't freeze.
			while (const auto event = Window.pollEvent())
			{
				if (event->is<Event::Closed>())
				{
					Window.close();
					bIsDelaying = false;
				}
			}
		}
		DelayTimer = 0.f;
	}

private:

	/* DELTA TIME */
	float DeltaT = 0.0f;

protected:
	
	// using this from my other project.
	static Engine* EngineInstance; // static pointer to the engine.
	
	/* registered objects */
	vector<Object*> RegisteredObjects;

	/* A regular RenderWindow */
	RenderWindow Window;

	/* player object */
	Player* CurrentPlayer;

	/* Input */
	Keyboard::Key LastKeyPressed = Keyboard::Key::Unknown;

	/* Debug */
	bool bShowCollisionDebug = false;
	bool bWasCollisionKeyPressed = false;

	/* delay related. */
	float DelayTimer = 0.f;
	float DelayDuration = 0.f;
	bool  bIsDelaying = false;

};