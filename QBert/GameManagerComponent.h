#pragma once
#include <BaseComponent.h>
#include <memory>
#include "GraphComponent.h"

namespace dae
{
    class GameObject;
}

class GameManagerComponent final :
    public BaseComponent
{
public:
    GameManagerComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~GameManagerComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;


    GameManagerComponent(const GameManagerComponent& other) = delete;
    GameManagerComponent(GameManagerComponent&& other) = delete;
    GameManagerComponent& operator=(const GameManagerComponent& other) = delete;
    GameManagerComponent& operator=(GameManagerComponent&& other) = delete;


private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<dae::GameObject> m_pTarget{ std::shared_ptr<dae::GameObject>(nullptr) };
    std::weak_ptr<GridNodeComponent> m_pGridLocation{ std::shared_ptr<GridNodeComponent>(nullptr) };

};

