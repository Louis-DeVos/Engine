#pragma once
#include "MiniginPCH.h"
#include <iostream>
#include "GameObject.h"

class Command
{
protected:
	dae::GameObject* GetActor() const { return m_Object; }

public:
	explicit Command(dae::GameObject* object) : m_Object{object} {};
	virtual ~Command() = default;
	virtual void Execute() = 0;
private:
	dae::GameObject* m_Object;
};

//class JumpCommand : public Command
//{
//public:
//	void Execute() override { GetActor()->Jump();}
//};
