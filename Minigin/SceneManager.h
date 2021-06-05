#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::weak_ptr<Scene> CreateScene(const std::string& name);

		void Update(float dt);
		void FixedUpdate(float dt);
		void Render();
		void DestroyObjects();
		~SceneManager();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
