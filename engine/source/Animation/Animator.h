#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

using namespace sf;
using namespace std;

struct AnimationClip
{
	// texture rects for each frame.
	vector<IntRect> Frames;

	// frames per second.
	float FrameRate = 8.0f;

	// loop
	bool bIsLooping = true;
};

class Animator
{
public:
	// add a clip by name
	void AddClip(const std::string& name, AnimationClip clip)
	{
		Clips[name] = clip;
	}

	// plays a clip by name
	void Play(const std::string& name)
	{
		// if its already playing
		if (CurrentClipName == name)
			return;

		CurrentClipName = name;
		CurrentFrame = 0;
		FrameTimer = 0.0f;
	}

	void Update(float DeltaTime)
	{
		if (Clips.empty() || CurrentClipName.empty())
			return;

		AnimationClip& clip = Clips[CurrentClipName];
		FrameTimer += DeltaTime;

		float FrameDuration = 1.0f / clip.FrameRate;

		if (FrameTimer >= FrameDuration)
		{
			FrameTimer -= FrameDuration;
			CurrentFrame++;

			if (CurrentFrame >= (int)clip.Frames.size())
			{
				CurrentFrame = clip.bIsLooping ? 0 : (int)clip.Frames.size() - 1;
			}
		}
	}

	// get the current frame rec tto pass to setTextureREct
	IntRect GetCurrentFrame() const
	{
		if (Clips.empty() || CurrentClipName.empty()) 
			return IntRect();
		
		const AnimationClip& clip = Clips.at(CurrentClipName);
		if (clip.Frames.empty()) return IntRect();
		return clip.Frames[CurrentFrame];
	}

	std::string GetCurrentClipName() const { return CurrentClipName; }

private:
	map<string, AnimationClip> Clips;
	string CurrentClipName;
	int CurrentFrame = 0;
	float FrameTimer = 0.0f;
};