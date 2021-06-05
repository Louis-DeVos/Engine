#pragma once
#include "../Minigin/Observer.h"
#include "LifeComponent.h"

class PlayerDeathObserver final: public Observer
{
public:
	PlayerDeathObserver(std::weak_ptr<LifeComponent> target);

	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event);
	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, int num);
	void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, const std::string& str);
private:
	std::weak_ptr<LifeComponent> m_pLifeComponent;
};

