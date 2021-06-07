#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
}

class DiskComponent final : public BaseComponent
{
public:
	DiskComponent(std::weak_ptr<dae::GameObject> pGameObject);

	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Render(const glm::vec3& transform) const override;
	std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

	glm::vec3 GetWorldPosition() const;

private:
	std::weak_ptr<dae::GameObject> m_pGameObject;
};

