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
	~PlayerDieCommand() { delete m_pPlayerComponent; }
	PlayerDieCommand(PlayerComponent* playerComponent);
	void Execute() override;
private:
	PlayerComponent* m_pPlayerComponent;
};
