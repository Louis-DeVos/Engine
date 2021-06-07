#pragma once
#include "../Minigin/Observer.h"
#include "ScoreComponent.h"
class ScoreObserver final:
    public Observer
{
public:
	ScoreObserver(std::weak_ptr<ScoreComponent> target);

	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event) override;
	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, int num) override;
	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, const std::string& str) override;
private:
	std::weak_ptr<ScoreComponent> m_pScoreComponent;
};

