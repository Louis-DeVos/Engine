#pragma once
#include "MiniginPCH.h"
#include "Transform.h"

class GameObject;

class BaseComponent
{

public:
	BaseComponent();
	virtual ~BaseComponent();

	virtual void Update(float dt)=0;
	virtual void FixedUpdate(float dt)=0;
	virtual void Render(const glm::vec3& transform) const =0;
	virtual std::weak_ptr<GameObject> GetOwner() const =0;
};

