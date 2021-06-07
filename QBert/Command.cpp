#include "Command.h"

MoveCommand::MoveCommand(std::weak_ptr<QBertComponent> qbertComponent, Direction pos)
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

CoilyMoveCommand::CoilyMoveCommand(std::weak_ptr<CoilyComponent> coilyComponent, Direction pos)
	:m_pCoilyComponent{ coilyComponent }
	, m_MovementDirection{ pos }
{

}

void CoilyMoveCommand::Execute()
{
	if (!m_pCoilyComponent.expired())
	{
		m_pCoilyComponent.lock()->Move(m_MovementDirection);
	}
}
