#pragma once
#include "BaseComponent.h"
#include <memory>
#include "GridNodeComponent.h"

namespace dae
{
    class GameObject;
}

class DiskComponent;

class QBertComponent final :
    public BaseComponent
{
public:
    QBertComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~QBertComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

    void GainScore(int score) const;
    void Die();
    int GetLives() const;

    QBertComponent(const QBertComponent& other) = delete;
    QBertComponent(QBertComponent&& other) = delete;
    QBertComponent& operator=(const QBertComponent& other) = delete;
    QBertComponent& operator=(QBertComponent&& other) = delete;

    void SetLocation(std::weak_ptr<GridNodeComponent> gridLocation);
    void SetStartLocation(std::weak_ptr<GridNodeComponent> gridLocation);

    void Move(Direction pos);

    void MoveOnDisk(std::weak_ptr<DiskComponent> disk);



    std::weak_ptr<GridNodeComponent> GetGridLocation() const { return m_pGridLocation; }

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    int m_Lives;
    std::weak_ptr<GridNodeComponent> m_pGridLocation;
    std::weak_ptr<GridNodeComponent> m_pStartLocation;
    std::weak_ptr<DiskComponent> m_pDisk;
    bool m_OnDisk{ false };
    float m_DiskTimer{ 0.f };
    const float m_DiskDelay{ 3.f };
    float m_MoveTimer{ 0.f };
    const float m_MoveDelay{ 0.1f };
};

