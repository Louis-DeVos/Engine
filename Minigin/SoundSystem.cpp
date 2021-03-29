#include "MiniginPCH.h"
#include "SoundSystem.h"

SoundSystem::SoundSystem()
	:m_Thread{&SoundSystem::Update,this}
{
}

SoundSystem::~SoundSystem()
{
	for (auto effect : m_EffectMap)
	{
		Mix_FreeChunk(effect.second);
	}
	
	for (auto music : m_MusicMap)
	{
		Mix_FreeMusic(music.second);
	}

	m_ShutDown = true;
	m_Thread.join();
}

void SoundSystem::Play(unsigned int id, bool music)
{
	m_SoundQueue.push(SoundInfo{ id,music });
}


void SoundSystem::AddEffect(std::string filePath, unsigned int id)
{
	m_EffectMap[id] = Mix_LoadWAV(filePath.c_str());
}

void SoundSystem::AddMusic(std::string filePath, unsigned int id)
{
	m_MusicMap[id] = Mix_LoadMUS(filePath.c_str());
}

void SoundSystem::Update()
{
	while (!m_ShutDown)
	{

		std::unique_lock<std::mutex> lock{ m_Mutex };


		if (!m_SoundQueue.empty())
		{
			if (m_SoundQueue.front().Music)
			{
				auto sound = m_MusicMap.find(m_SoundQueue.front().Id);
				if (sound != m_MusicMap.end())
				{
					Mix_PlayMusic((*sound).second, -1);
				}
			}
			else
			{
				auto sound = m_EffectMap.find(m_SoundQueue.front().Id);

				if (sound != m_EffectMap.end())
				{
					Mix_PlayChannel(-1, (*sound).second, 0);
				}
			}
			m_SoundQueue.pop();

		}
		lock.unlock();
	}
}
