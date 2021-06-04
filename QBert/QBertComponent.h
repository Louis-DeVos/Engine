#pragma once
#include "BaseComponent.h"
#include <memory>
#include "GraphComponent.h"

namespace dae
{
    class GameObject;
}

class QBertComponent final :
    public BaseComponent
{
public:
    QBertComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~QBertComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void GainScore(int score);
    void Die();
    int GetLives();

    QBertComponent(const QBertComponent& other) = delete;
    QBertComponent(QBertComponent&& other) = delete;
    QBertComponent& operator=(const QBertComponent& other) = delete;
    QBertComponent& operator=(QBertComponent&& other) = delete;

    void SetLocation(std::weak_ptr<GridNodeComponent> gridLocation);

    void Move(Position pos);

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    int m_Lives;
    std::weak_ptr<GridNodeComponent> m_pGridLocation;
};

