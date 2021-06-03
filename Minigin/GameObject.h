#pragma once
#include "Transform.h"
#include "BaseComponent.h"
#include <vector>
#include <memory>

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update(float dt);
		void FixedUpdate(float dt);
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		const Transform& GetTransform() { return m_Transform; }
		void AddComponent(std::shared_ptr<BaseComponent> pComponent) { m_ComponentList.push_back(pComponent); }

		bool ToBeDestroyed();
		void SetToBeDestroyed();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		std::weak_ptr<T> getComponent();

	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<BaseComponent>> m_ComponentList;
		bool m_ToBeDestroyed{ false };
	};
	template<typename T>
	inline std::weak_ptr<T> GameObject::getComponent()
	{
		for (std::shared_ptr<BaseComponent> pComponent : m_ComponentList)
		{
			auto ptr = std::dynamic_pointer_cast<T>(pComponent);
			if (ptr)
			{
				return std::weak_ptr<T>(ptr);
			}
		}
		return std::weak_ptr<T>();
	}
}
