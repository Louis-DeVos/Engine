#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GridnodeComponent.h"

namespace dae
{
    class GameObject;
}
class QBertComponent;
class CoilyComponent;
class PurpleEnemyComponent;
class GreenEnemyComponent;
class LifeComponent;
class ScoreComponent;
class DiskComponent;
class MenuComponent;

class GameManagerComponent final :
    public BaseComponent
{
public:
    GameManagerComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~GameManagerComponent() override = default;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;

    void CheckCollisions();

    void SpawnCoily();
    void SpawnPurpleEnemy();
    void SpawnGreenEnemy();

    void OnQBertDeath(std::weak_ptr<QBertComponent> qbert);
    void reset();
    void StartSinglePlayer();
    void StartCoop();
    void StartVersus();
    std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

    void LoadLevel();


    GameManagerComponent(const GameManagerComponent& other) = delete;
    GameManagerComponent(GameManagerComponent&& other) = delete;
    GameManagerComponent& operator=(const GameManagerComponent& other) = delete;
    GameManagerComponent& operator=(GameManagerComponent&& other) = delete;


private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<QBertComponent> m_pPlayer{ std::shared_ptr<QBertComponent>(nullptr) };
    std::weak_ptr<QBertComponent> m_pPlayer2{ std::shared_ptr<QBertComponent>(nullptr) };
    std::weak_ptr<CoilyComponent> m_pCoily{ std::shared_ptr<CoilyComponent>(nullptr) };
    std::vector<std::weak_ptr<GreenEnemyComponent>> m_GreenEnemies{};
    std::vector<std::weak_ptr<PurpleEnemyComponent>> m_PurpleEnemies{};
    std::vector<std::weak_ptr<GridNodeComponent>> m_Nodes{};
    std::vector<std::weak_ptr<DiskComponent>> m_Disks{};
    std::weak_ptr<GridNodeComponent> m_pStartNode{ std::shared_ptr<GridNodeComponent>(nullptr) };
    std::weak_ptr<ScoreComponent> m_pScoreCounter{ std::shared_ptr<ScoreComponent>(nullptr) };
    std::weak_ptr<LifeComponent> m_pLifeCounter{ std::shared_ptr<LifeComponent>(nullptr) };
    std::weak_ptr<LifeComponent> m_pLifeCounter2{ std::shared_ptr<LifeComponent>(nullptr) };
    std::weak_ptr<MenuComponent> m_pMenu{ std::shared_ptr<MenuComponent>(nullptr) };

    const float m_EnemySpawnDelay{ 3.f };
    float m_EnemySpawnTimer{ 0.f };
    bool m_EnemiesCleared{ false };
    bool m_LevelLoaded{ false };
    int m_Currentlevel{ 1 };
    const int m_maxLevel{ 3 };
    bool m_Coop{ false };
    bool m_Versus{false};
};

