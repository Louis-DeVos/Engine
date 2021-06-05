#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GraphComponent.h"

namespace dae
{
    class GameObject;
}
class QBertComponent;
class CoilyComponent;
class PurpleEnemyComponent;
class GreenEnemyComponent;

class GameManagerComponent final :
    public BaseComponent
{
public:
    GameManagerComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~GameManagerComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void CheckCollisions();


    GameManagerComponent(const GameManagerComponent& other) = delete;
    GameManagerComponent(GameManagerComponent&& other) = delete;
    GameManagerComponent& operator=(const GameManagerComponent& other) = delete;
    GameManagerComponent& operator=(GameManagerComponent&& other) = delete;


private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<QBertComponent> m_pPlayer{ std::shared_ptr<QBertComponent>(nullptr) };
    std::weak_ptr<CoilyComponent> m_pCoily{ std::shared_ptr<CoilyComponent>(nullptr) };
    std::vector<std::weak_ptr<GreenEnemyComponent>> m_GreenEnemies{};
    std::vector<std::weak_ptr<PurpleEnemyComponent>> m_PurpleEnemies{};
    std::weak_ptr<GridNodeComponent> m_pStartNode{ std::shared_ptr<GridNodeComponent>(nullptr) };

};

