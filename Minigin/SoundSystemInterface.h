#pragma once
#include <string>

class SoundSystemInterface
{
public:
	SoundSystemInterface() = default;
	virtual ~SoundSystemInterface() = default;

	virtual void Play(unsigned int id, bool music) = 0;
	virtual void AddEffect(std::string filePath, unsigned int id) = 0;
	virtual void AddMusic(std::string filePath, unsigned int id) = 0;

	virtual void Update() = 0;

};