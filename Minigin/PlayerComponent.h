#pragma once
#include "BaseComponent.h"

namespace dae
{
    class GameObject;
}

class PlayerComponent final :
    public BaseComponent
{
public:
    PlayerComponent(dae::GameObject* pGameObject);
    ~PlayerComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void Die() { --m_Lives; };

    PlayerComponent(const PlayerComponent& other) = delete;
    PlayerComponent(PlayerComponent&& other) = delete;
    PlayerComponent& operator=(const PlayerComponent& other) = delete;
    PlayerComponent& operator=(PlayerComponent&& other) = delete;

private:
    dae::GameObject* m_pGameObject;
    int m_Lives;
};

