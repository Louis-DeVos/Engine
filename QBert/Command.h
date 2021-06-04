#pragma once
#include "../Minigin/Command.h"
#include "QBertComponent.h"

class MoveCommand final : public Command
{
public:
	MoveCommand(std::weak_ptr<QBertComponent> qbertComponent, Position pos);
	void Execute() override;
private:
	std::weak_ptr<QBertComponent> m_pQBertComponent;
	Position m_MovementDirection;
};
