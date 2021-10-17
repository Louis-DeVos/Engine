#pragma once
#include "BaseComponent.h"
#include <memory>


class GameObject;

class PlayerComponent final :
    public BaseComponent
{
public:
    PlayerComponent(std::weak_ptr<GameObject> pGameObject);
    ~PlayerComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;

    void GainScore(int score) const;
    void Die();
    int GetLives() const;
    std::weak_ptr<GameObject> GetOwner() const override { return m_pGameObject; }

    PlayerComponent(const PlayerComponent& other) = delete;
    PlayerComponent(PlayerComponent&& other) = delete;
    PlayerComponent& operator=(const PlayerComponent& other) = delete;
    PlayerComponent& operator=(PlayerComponent&& other) = delete;

private:
    std::weak_ptr<GameObject> m_pGameObject;
    int m_Lives;
};

