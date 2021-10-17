#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"


class FPSComponent final :
    public BaseComponent
{
public:
    FPSComponent(std::weak_ptr<GameObject> pGameObject);
    ~FPSComponent() override;

    void Update(float dt) override;
    void FixedUpdate(float dt) override;
    void Render(const glm::vec3& transform) const override;
    std::weak_ptr<GameObject> GetOwner() const override { return m_pGameObject; }

    FPSComponent(const FPSComponent& other) = delete;
    FPSComponent(FPSComponent&& other) = delete;
    FPSComponent& operator=(const FPSComponent& other) = delete;
    FPSComponent& operator=(FPSComponent&& other) = delete;

private:
    std::weak_ptr<GameObject> m_pGameObject;
    std::weak_ptr<TextComponent> m_pTextComponent;
    int m_FPS;
};

