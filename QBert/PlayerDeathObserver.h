#pragma once
#include "../Minigin/Observer.h"
#include "LifeComponent.h"

class PlayerDeathObserver final: public Observer
{
public:
	PlayerDeathObserver(std::weak_ptr<LifeComponent> target);

	void OnNotify(std::weak_ptr<GameObject> pGameObject, Event event) override;
	void OnNotify(std::weak_ptr<GameObject> pGameObject, Event event, int num) override;
	void OnNotify(std::weak_ptr<GameObject> pGameObject, Event event, const std::string& str) override;
private:
	std::weak_ptr<LifeComponent> m_pLifeComponent;
};

