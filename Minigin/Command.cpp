#include "MiniginPCH.h"
#include "Command.h"

PlayerDieCommand::PlayerDieCommand(std::weak_ptr<PlayerComponent> playerComponent)
	:m_pPlayerComponent(playerComponent)
{
}

void PlayerDieCommand::Execute()
{
	if (!m_pPlayerComponent.expired())
	{
		m_pPlayerComponent.lock()->Die();
	}
}

GainScoreCommand::GainScoreCommand(std::weak_ptr<PlayerComponent> playerComponent, int score)
	:m_pPlayerComponent{playerComponent}
	, m_GainedScore{score}
{
}

void GainScoreCommand::Execute()
{
	if (!m_pPlayerComponent.expired())
	{
		m_pPlayerComponent.lock()->GainScore(m_GainedScore);
	}
}
