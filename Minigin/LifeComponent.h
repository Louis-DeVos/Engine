#pragma once
#include "BaseComponent.h"

namespace dae
{
    class GameObject;
}

class LifeComponent :
    public BaseComponent
{
public:
    LifeComponent(dae::GameObject* pGameObject);
    ~LifeComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;


    LifeComponent(const LifeComponent& other) = delete;
    LifeComponent(LifeComponent&& other) = delete;
    LifeComponent& operator=(const LifeComponent& other) = delete;
    LifeComponent& operator=(LifeComponent&& other) = delete;

private:
    dae::GameObject* m_pGameObject;
    int m_Lives;
};

