#pragma once
#include "BaseComponent.h"

namespace dae
{
    class GameObject;
    class TextComponent;
}

class ScoreComponent final:
    public BaseComponent
{
public:
    ScoreComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~ScoreComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    void AddScore(int score);
    std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

    ScoreComponent(const ScoreComponent& other) = delete;
    ScoreComponent(ScoreComponent&& other) = delete;
    ScoreComponent& operator=(const ScoreComponent& other) = delete;
    ScoreComponent& operator=(ScoreComponent&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<dae::TextComponent> m_pTextComponent;
    int m_Score;
    bool m_NeedsUpdate{ true };
};

