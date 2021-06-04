#include "Command.h"

MoveCommand::MoveCommand(std::weak_ptr<QBertComponent> qbertComponent, Position pos)
	:m_pQBertComponent{ qbertComponent }
	,m_MovementDirection{pos}
{
}

void MoveCommand::Execute()
{
	if (!m_pQBertComponent.expired())
	{
		m_pQBertComponent.lock()->Move(m_MovementDirection);
	}
}
