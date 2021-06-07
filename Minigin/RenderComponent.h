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
    ~RenderComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;

    void SetTexture(std::shared_ptr<dae::Texture2D> pTexture);
    std::weak_ptr<dae::GameObject> GetOwner() const override { return m_pGameObject; }

    RenderComponent(const RenderComponent& other) = delete;
    RenderComponent(RenderComponent&& other) = delete;
    RenderComponent& operator=(const RenderComponent& other) = delete;
    RenderComponent& operator=(RenderComponent&& other) = delete;

private:
    std::weak_ptr<dae::GameObject> m_pGameObject;
    std::shared_ptr<dae::Texture2D> m_pTexture;
};

