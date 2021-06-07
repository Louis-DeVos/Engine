#pragma once
#include "../Minigin/Command.h"
#include "QBertComponent.h"
#include "CoilyComponent.h"

class MoveCommand final : public Command
{
public:
	MoveCommand(std::weak_ptr<QBertComponent> qbertComponent, Direction pos);
	void Execute() override;
private:
	std::weak_ptr<QBertComponent> m_pQBertComponent;
	Direction m_MovementDirection;
};

class CoilyMoveCommand final : public Command
{
public:
	CoilyMoveCommand(std::weak_ptr<CoilyComponent> coilyComponent, Direction pos);
	void Execute() override;
private:
	std::weak_ptr<CoilyComponent> m_pCoilyComponent;
	Direction m_MovementDirection;
};
