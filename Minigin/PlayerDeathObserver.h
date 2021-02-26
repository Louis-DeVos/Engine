#pragma once
#include "Observer.h"

class PlayerDeathObserver final: public Observer
{
public:
	PlayerDeathObserver();

	void OnNotify(dae::GameObject* pGameObject, Event event);

};

