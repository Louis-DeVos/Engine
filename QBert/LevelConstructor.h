#pragma once
#include <string>
#include <memory>
#include "GridNodeComponent.h"



class GameObject;
class Scene;

class LevelConstructor final
{
public:
	LevelConstructor();
	~LevelConstructor();

	std::pair<std::vector< std::weak_ptr<GridNodeComponent>>, std::vector< std::weak_ptr<DiskComponent>>> CreateLevel(std::weak_ptr<Scene> pScene, std::string filePath) const;

private:
	const int m_StartX{320};
	const int m_StartY{100};
	const int m_SizeX{32};
	const int m_SizeY{32};
};

