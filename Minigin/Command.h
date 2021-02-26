#pragma once
#include "MiniginPCH.h"
#include <iostream>
#include "GameObject.h"
#include "PlayerComponent.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class PlayerDieCommand final : public Command
{
public:
	PlayerDieCommand(std::weak_ptr<PlayerComponent> playerComponent);
	void Execute() override;
private:
	std::weak_ptr<PlayerComponent> m_pPlayerComponent;
};

class GainScoreCommand final : public Command
{
public:
	GainScoreCommand(std::weak_ptr<PlayerComponent> playerComponent, int score);
	void Execute() override;
private:
	std::weak_ptr<PlayerComponent> m_pPlayerComponent;
	int m_GainedScore;
};
