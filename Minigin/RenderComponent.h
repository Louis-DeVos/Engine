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
    RenderComponent(std::weak_ptr<dae::GameObject> pGameObject);
    ~RenderComponent();

    void Update(float dt);
    void FixedUpdate(float dt);
    void Render(const glm::vec3& transform) const;

    void SetTexture(std::shared_ptr<dae::Texture2D> pTexture);

    RenderComponent(const RenderComponent& other) = delete;
    RenderComponent(RenderComponent&& other) = delete;
    RenderComponent& operator=(const RenderComponent& other) = delete;
    RenderComponent& operator=(RenderComponent&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::shared_ptr<dae::Texture2D> m_pTexture;
};

