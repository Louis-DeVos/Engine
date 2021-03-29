#pragma once
#include "SoundSystemInterface.h"




class NullSoundSystem final : public SoundSystemInterface
{
public:
	NullSoundSystem() {};
	~NullSoundSystem() {};
	NullSoundSystem(const NullSoundSystem&) = delete;
	NullSoundSystem(NullSoundSystem&&) = delete;
	NullSoundSystem& operator=(const NullSoundSystem&) = delete;
	NullSoundSystem& operator=(NullSoundSystem&&) = delete;



	void Play(unsigned int, bool) {};
	void AddEffect(std::string, unsigned int ) {};
	void AddMusic(std::string, unsigned int ) {};

	void Update() {};

private:

};


class ServiceLocator
{

	static SoundSystemInterface* m_pSSInstance;
	static NullSoundSystem m_DefaultSS;




public:
	static SoundSystemInterface* GetSoundSystem() { return m_pSSInstance; }
	static void RegisterSoundSystem(SoundSystemInterface* ss)
	{
		m_pSSInstance = (ss == nullptr) ? &m_DefaultSS : ss;
	}
};
