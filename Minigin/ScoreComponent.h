#pragma once
#include "BaseComponent.h"

namespace dae
{
    class GameObject;
}

class ScoreComponent :
    public BaseComponent
{
public:
    ScoreComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~ScoreComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;
    void AddScore(int score);

    ScoreComponent(const ScoreComponent& other) = delete;
    ScoreComponent(ScoreComponent&& other) = delete;
    ScoreComponent& operator=(const ScoreComponent& other) = delete;
    ScoreComponent& operator=(ScoreComponent&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    int m_Score;
    bool m_NeedsUpdate{ true };
};

