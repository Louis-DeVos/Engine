#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
    class GameObject;
    class TextComponent;
}

class LifeComponent final:
    public BaseComponent
{
public:
    LifeComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~LifeComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    void SetLives(int lives);
    std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

    LifeComponent(const LifeComponent& other) = delete;
    LifeComponent(LifeComponent&& other) = delete;
    LifeComponent& operator=(const LifeComponent& other) = delete;
    LifeComponent& operator=(LifeComponent&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<dae::TextComponent> m_pTextComponent;
    int m_Lives;
    bool m_NeedsUpdate{ true };
};

