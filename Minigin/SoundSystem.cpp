#include "MiniginPCH.h"
#include "SoundSystem.h"

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
	}
}
