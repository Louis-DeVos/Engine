#pragma once
#include <string>
#include <memory>
#include "GraphComponent.h"

namespace dae
{
	class GameObject;
	class Scene;
}


class LevelConstructor
{
public:
	LevelConstructor();
	~LevelConstructor();

	std::weak_ptr<GridNodeComponent> CreateLevel(std::weak_ptr<dae::Scene> pScene, std::string filePath) const;

private:
	const int m_StartX{320};
	const int m_StartY{100};
	const int m_SizeX{32};
	const int m_SizeY{32};
};

