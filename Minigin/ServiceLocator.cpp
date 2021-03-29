#include "MiniginPCH.h"
#include "ServiceLocator.h"


NullSoundSystem ServiceLocator::m_DefaultSS;
SoundSystemInterface* ServiceLocator::m_pSSInstance = &m_DefaultSS;