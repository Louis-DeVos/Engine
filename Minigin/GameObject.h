#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update(float dt) override;
		void FixedUpdate(float dt) override;
		void Render() const override;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		void AddComponent(BaseComponent* pComponent) { m_ComponentList.push_back(pComponent); }

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		T* getComponent();

	private:
		Transform m_Transform;
		std::vector<BaseComponent*> m_ComponentList;
	};
	template<typename T>
	inline T* GameObject::getComponent()
	{
		for (BaseComponent* pComponent : m_ComponentList)
		{
			if (dynamic_cast<T*>(pComponent))
			{
				return (T*)pComponent;
			}
		}
		return nullptr;
	}
}