#pragma once
#include "BaseComponent.h"
#include <memory>

namespace dae
{
    class GameObject;
}

class PlayerComponent final :
    public BaseComponent
{
public:
    PlayerComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~PlayerComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void GainScore(int score);
    void Die();
    int GetLives();

    PlayerComponent(const PlayerComponent& other) = delete;
    PlayerComponent(PlayerComponent&& other) = delete;
    PlayerComponent& operator=(const PlayerComponent& other) = delete;
    PlayerComponent& operator=(PlayerComponent&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    int m_Lives;
};

