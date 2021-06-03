#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
    class GameObject;
}

class LifeComponent :
    public BaseComponent
{
public:
    LifeComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~LifeComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;
    void SetLives(int lives);

    LifeComponent(const LifeComponent& other) = delete;
    LifeComponent(LifeComponent&& other) = delete;
    LifeComponent& operator=(const LifeComponent& other) = delete;
    LifeComponent& operator=(LifeComponent&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    int m_Lives;
    bool m_NeedsUpdate{ true };
};

