#pragma once
#include "GameObject.h"

enum class Event
{

};


class Observer
{
public:
	virtual void OnNotify(dae::GameObject* pGameObject, Event event);
};

