#include "SoundManager.h"
#include "Constants.h"
#include <iostream>
#include <filesystem>

using namespace std;

SoundManager::SoundManager()
{
	// automatically preload all avaliable sounds into memory
	for (auto& entry : filesystem::directory_iterator("content/sounds"))
	{
		string ext = entry.path().extension().string();
		// check for wav ogg flac audio files.
		if (ext == ".wav" || ext == ".ogg" || ext == ".flac")
		{
			string fullFilePath = entry.path().string();
			string fileName = entry.path().filename().string();

			// skips if it already loaded
			if (Buffers.find(fileName) != Buffers.end())
				continue;

			SoundBuffer buffer;
			
			if (!buffer.loadFromFile(fullFilePath))
			{
				Message("ERROR! Failed to load sound: " << fileName << "\n")
				Message("Ensure that the audio file you loaded is valid or exists!")
				continue;
			}
			Buffers[fileName] = buffer;
			Sounds[fileName] = make_unique<Sound>(Buffers[fileName]);

		}
	}
}
void SoundManager::PlaySound(const string& fileName, float volume, bool bLoop)
{

	// let's resolve the actual path first.
	string resolvedAudioPath = ResolvePath(fileName);

	// let's load our audio.
	if (Buffers.find(resolvedAudioPath) == Buffers.end())
	{
		SoundBuffer buffer;
		if (!buffer.loadFromFile(resolvedAudioPath))
		{
			Message("ERROR! Failed to load sound: " << resolvedAudioPath << "\n")
			Message("Ensure that the audio file you loaded is valid or exists!")
			return;
		}
		Buffers[resolvedAudioPath] = buffer;
		Sounds[resolvedAudioPath] = make_unique<Sound>(Buffers[resolvedAudioPath]);
	}

	// we'll allow loops assuming bLoop is set to true.
	Sounds[resolvedAudioPath]->setVolume(volume);
	Sounds[resolvedAudioPath]->setLooping(bLoop);
	Sounds[resolvedAudioPath]->play();
}

void SoundManager::PlaySoundPooled(const string& fileName, float volume)
{
	string resolvedFile = ResolvePath(fileName);

	// load buffer if needed.
	if (Buffers.find(resolvedFile) == Buffers.end())
	{
		SoundBuffer buffer;
		if (!buffer.loadFromFile(resolvedFile))
		{
			Message("PlaySoundPooled: FAILED TO LOAD: " << resolvedFile);
			Message("Ensure that the file is valid and try again!");
			return;
		}
		Buffers[resolvedFile] = buffer;
	}

	// creates a pool of 8 instances if one does not exist.
	if (SoundPool.find(resolvedFile) == SoundPool.end())
	{
		SoundPool[resolvedFile].reserve(8);

		// we must now construct with buffers instead.
		for (int i = 0; i < 8; i++)
		{
			SoundPool[resolvedFile].push_back(make_unique<Sound>(Buffers[resolvedFile]));
		}
		PoolIndex[resolvedFile] = 0;
	}

	// get the next avaliabel sound in pool
	int& index = PoolIndex[resolvedFile];
	Sound& sound = *SoundPool[resolvedFile][index];
	sound.setVolume(volume);
	sound.play();

	// advance to the next slot.
	index = (index + 1) % SoundPool[resolvedFile].size();
}

void SoundManager::StopSound(const string& fileName)
{
	// let's resolve the actual path first.
	string resolvedAudioPath = ResolvePath(fileName);

	auto it = Sounds.find(fileName);
	if (it != Sounds.end())
	{
		it->second->stop();
	}
}

void SoundManager::StopAll()
{
	for (auto& pair : Sounds)
		pair.second->stop();
}

string SoundManager::ResolvePath(const string& fileName)
{
	// if we get the full path
	if (fileName.find("content/") != string::npos)
		return fileName;

	// if we just get the file name or subdirectory.
	// such as "snd_fortressman.wav" or "content/sounds/limbo/snd_crystal_whoosh.wav"
	// then we'll just resolve to content/sounds/.
	return "content/sounds/" + fileName;
}