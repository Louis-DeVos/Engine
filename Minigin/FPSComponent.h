#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
    class GameObject;
}
class FPSComponent final :
    public BaseComponent
{
public:
    FPSComponent(dae::GameObject* pGameObject);
    ~FPSComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    FPSComponent(const FPSComponent& other) = delete;
    FPSComponent(FPSComponent&& other) = delete;
    FPSComponent& operator=(const FPSComponent& other) = delete;
    FPSComponent& operator=(FPSComponent&& other) = delete;

private:
    dae::GameObject* m_pGameObject;
    int m_FPS;
};

