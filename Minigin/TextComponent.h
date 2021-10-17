#pragma once
#include "SceneObject.h"
#include "Transform.h"
#include "BaseComponent.h"
#include "RenderComponent.h"



class GameObject;


class Font;
class Texture2D;
class TextComponent final : public BaseComponent
{
public:
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Render(const glm::vec3& transform) const override;

	void SetText(const std::string& text);
	std::weak_ptr<GameObject> GetOwner() const override { return m_pGameObject; }

	explicit TextComponent(const std::string& text, std::shared_ptr<Font> font, std::weak_ptr<GameObject> pGameObject);
	~TextComponent() override;
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;
private:
	std::weak_ptr<GameObject> m_pGameObject;
	std::weak_ptr<RenderComponent> m_pRenderComponent;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
	bool m_NeedsUpdate;
};

