#include "MiniginPCH.h"
#include "PlayerDeathObserver.h"
#include "PlayerComponent.h"

PlayerDeathObserver::PlayerDeathObserver(std::weak_ptr<LifeComponent> target)
	: m_pLifeComponent{target}
{
	
}

void PlayerDeathObserver::OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event)
{
	switch (event)
	{
	case Event::KillEvent:
		m_pLifeComponent.lock()->SetLives(pGameObject.lock()->getComponent<PlayerComponent>().lock()->GetLives());
		std::cout << "PlayerDied\n";
		break;
	default:
		break;
	}
}

void PlayerDeathObserver::OnNotify(std::weak_ptr<dae::GameObject> , Event , int )
{
}

void PlayerDeathObserver::OnNotify(std::weak_ptr<dae::GameObject> , Event , const std::string& )
{
}
