#pragma once
#include "BaseComponent.h"


class GameObject;


class DiskComponent final : public BaseComponent
{
public:
	DiskComponent(std::weak_ptr<GameObject> pGameObject);

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Render(const glm::vec3& transform) const override;
	std::weak_ptr<GameObject> GetOwner() const override { return m_pGameObject; }

	glm::vec3 GetWorldPosition() const;

private:
	std::weak_ptr<GameObject> m_pGameObject;
};

