#include "MiniginPCH.h"
#include "Command.h"

PlayerDieCommand::PlayerDieCommand(PlayerComponent* playerComponent)
	:m_pPlayerComponent(playerComponent)
{
}

void PlayerDieCommand::Execute()
{
	if (m_pPlayerComponent != nullptr)
	{
		m_pPlayerComponent->Die();
	}
}

