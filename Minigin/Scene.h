#pragma once
#include "SceneManager.h"
#include <string>

class GameObject;
class Scene final
{
	friend std::weak_ptr<Scene> SceneManager::CreateScene(const std::string& name);
public:
	void Add(std::shared_ptr<GameObject> object);

	void Update(float dt);
	void FixedUpdate(float dt);
	void Render() const;
	void DestroyObjects();

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector <std::shared_ptr<GameObject>> m_Objects{};

	static unsigned int m_IdCounter; 
};


