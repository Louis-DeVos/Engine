#pragma once
#include "Observer.h"
#include "ScoreComponent.h"
class ScoreObserver :
    public Observer
{
public:
	ScoreObserver(std::weak_ptr<ScoreComponent> target);

	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event);
	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, int num);
	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, const std::string& str);
private:
	std::weak_ptr<ScoreComponent> m_pScoreComponent;
};

