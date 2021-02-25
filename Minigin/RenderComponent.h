#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae
{
    class GameObject;
}

class RenderComponent final:
    public BaseComponent
{
public:
    RenderComponent(dae::GameObject* pGameObject);
    ~RenderComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void SetTexture(dae::Texture2D* pTexture);

    RenderComponent(const RenderComponent& other) = delete;
    RenderComponent(RenderComponent&& other) = delete;
    RenderComponent& operator=(const RenderComponent& other) = delete;
    RenderComponent& operator=(RenderComponent&& other) = delete;

private:
    dae::GameObject* m_pGameObject;
    dae::Texture2D* m_pTexture;
};

