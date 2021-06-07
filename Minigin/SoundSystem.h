#pragma once
#include "SoundSystemInterface.h"
#include <string>
#include <queue>
#include <map>
#include <thread>
#include <mutex>
//#include "../3rdParty/SDL2_mixer/include/SDL_mixer.h"
#include <SDL_mixer.h>





struct SoundInfo
{
	unsigned int Id;
	bool Music;
};

class SoundSystem final:
    public SoundSystemInterface
{
public:
	SoundSystem();
	~SoundSystem() override;
	SoundSystem(const SoundSystem&) = delete;
	SoundSystem(SoundSystem&&) = delete;
	SoundSystem& operator=(const SoundSystem&) = delete;
	SoundSystem& operator=(SoundSystem&&) = delete;



	void Play(unsigned int id, bool music) override;
	void AddEffect(std::string filePath, unsigned int id) override;
	void AddMusic(std::string filePath, unsigned int id) override;
	void Update() override;



private:
	std::map<unsigned int, Mix_Chunk*> m_EffectMap;
	std::map<unsigned int, Mix_Music*> m_MusicMap;
	std::queue<SoundInfo> m_SoundQueue;

	std::thread m_Thread;
	std::mutex m_Mutex;
	//std::condition_variable m_ConditionVariable;
	bool m_ShutDown{false};

};

