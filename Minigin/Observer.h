#pragma once
#include "GameObject.h"

enum class Event
{
	KillEvent,
	ChangeScoreEvent
};


class Observer
{
public:
	virtual ~Observer() {};
	virtual void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event) = 0;
	virtual void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, int num) = 0;
	virtual void OnNotify(std::weak_ptr<dae::GameObject> pGameObject, Event event, const std::string& str) = 0;
};

