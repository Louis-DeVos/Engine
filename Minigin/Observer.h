#pragma once
#include "GameObject.h"

enum class Event
{

};


class Observer
{
public:
	virtual ~Observer() {};
	virtual void OnNotify(dae::GameObject* pGameObject, Event event) = 0;
};

