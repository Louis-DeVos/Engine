#pragma once
#include <BaseComponent.h>

namespace dae
{
    class GameObject;
}

class GameManagerComponent;

class MenuComponent final:
    public BaseComponent
{
public:
    MenuComponent(std::weak_ptr<dae::GameObject> pGameObject, std::weak_ptr<GameManagerComponent> pManager);
    ~MenuComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

    MenuComponent(const MenuComponent& other) = delete;
    MenuComponent(MenuComponent&& other) = delete;
    MenuComponent& operator=(const MenuComponent& other) = delete;
    MenuComponent& operator=(MenuComponent&& other) = delete;



private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::weak_ptr<GameManagerComponent> m_pGameManager;
};

