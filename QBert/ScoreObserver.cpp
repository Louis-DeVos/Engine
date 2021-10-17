#include "MiniginPCH.h"
#include "ScoreObserver.h"
#include <memory>
#include <iostream>
#include <string>

ScoreObserver::ScoreObserver(std::weak_ptr<ScoreComponent> target)
	:m_pScoreComponent{target}
{
}

void ScoreObserver::OnNotify(std::weak_ptr<GameObject>, Event )
{
}

void ScoreObserver::OnNotify(std::weak_ptr<GameObject> pGameObject, Event event, int num)
{
	switch (event)
	{
	case Event::ChangeScoreEvent:
		m_pScoreComponent.lock()->AddScore(num);
		std::cout << "Player gained " << num << " score\n";
		break;
	default:
		break;
	}
}

void ScoreObserver::OnNotify(std::weak_ptr<GameObject>, Event , const std::string& )
{
}
