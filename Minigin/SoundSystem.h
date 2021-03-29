#pragma once
#include "SoundSystemInterface.h"
#include <string>
#include <queue>
#include <map>


class SoundSystem final:
    public SoundSystemInterface
{
public:
	SoundSystem() {};
	~SoundSystem() {};
	SoundSystem(const SoundSystem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	SoundSystem& operator=(const SoundSystem&) = delete;
	SoundSystem& operator=(SoundSystem&&) = delete;



	void Play(unsigned int id, bool music);
	void AddEffect(std::string filePath, unsigned int id);
	void AddMusic(std::string filePath, unsigned int id);
	void Update();


private:
	std::map<unsigned int, Mix_Chunk*> m_EffectMap;
	std::map<unsigned int, Mix_Music*> m_MusicMap;
	std::queue<SoundInfo> m_SoundQueue;



};

struct SoundInfo
{
	unsigned int Id;
	bool Music;
};
