#include "LevelConstructor.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/Scene.h"
#include <fstream>
#include <regex>
#include "DiskComponent.h"

LevelConstructor::LevelConstructor()
= default;

LevelConstructor::~LevelConstructor()
= default;

std::pair<std::vector< std::weak_ptr<GridNodeComponent>>, std::vector< std::weak_ptr<DiskComponent>>> LevelConstructor::CreateLevel(std::weak_ptr<Scene> pScene, std::string filePath) const
{
	std::ifstream file{ filePath };

	std::string str{};

	std::smatch match{};


	int layers{};
	bool cycle{};
	int maxState{};

	while (file.good())
	{
		std::getline(file,str);
		if (std::regex_match(str, match, std::regex{ "([a-zA-Z]+)\\s?=\\s?([0-9A-Za-z]+)" }))
		{
			if (match[1] == "Layers")
			{
				layers = std::stoi(match[2]);
			}
			if (match[1] == "Cycle")
			{
				cycle = match[2] == "true";
			}
			if (match[1] == "NeededJumps")
			{
				maxState = std::stoi(match[2]);
			}
		}

	}


	std::shared_ptr<GameObject> StartNode = std::make_shared<GameObject>(pScene);
	auto render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(StartNode));
	render->SetTexture(ResourceManager::GetInstance().LoadTexture("Block_0.png"));
	StartNode->AddComponent(render);
	auto startNodeComp = std::make_shared<GridNodeComponent>(StartNode);
	StartNode->AddComponent(startNodeComp);
	StartNode->SetPosition(float(m_StartX), float(m_StartY));
	pScene.lock()->Add(StartNode);

	startNodeComp->SetMaxState(maxState);
	startNodeComp->SetCycle(cycle);



	std::vector< std::weak_ptr<GridNodeComponent>> lastLayer{};
	std::vector< std::weak_ptr<GridNodeComponent>> currentLayer{};
	std::vector< std::weak_ptr<GridNodeComponent>> nodes{};
	lastLayer.push_back(StartNode->getComponent<GridNodeComponent>());
	nodes.push_back(StartNode->getComponent<GridNodeComponent>());




	//std::shared_ptr<GameObject> disk = std::make_shared<GameObject>(pScene);
	//render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(disk));
	//render->SetTexture(ResourceManager::GetInstance().LoadTexture("Disk.png"));
	//disk->AddComponent(render);
	//auto diskComp = std::make_shared<DiskComponent>(disk);
	//disk->AddComponent(diskComp);
	//disk->SetPosition(m_StartX - m_SizeX / 2.f , m_StartY - m_SizeY * 0.75f );
	//pScene.lock()->Add(disk);

	//startNodeComp->SetLeftDisk(diskComp);


	std::vector< std::weak_ptr<DiskComponent>> disks{};
	//disks.push_back(diskComp);


	for (size_t i = 1; i < size_t(layers); i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			std::shared_ptr<GameObject> Node = std::make_shared<GameObject>(pScene);
			render = std::make_shared<RenderComponent>(std::weak_ptr<GameObject>(Node));
			render->SetTexture(ResourceManager::GetInstance().LoadTexture("Block_0.png"));
			Node->AddComponent(render);
			auto nodeComp = std::make_shared<GridNodeComponent>(Node);
			Node->AddComponent(nodeComp);
			Node->SetPosition(m_StartX -m_SizeX/2.f*i + m_SizeX*j, m_StartY + m_SizeY*0.75f*i);
			pScene.lock()->Add(Node);

			nodeComp->SetMaxState(maxState);
			nodeComp->SetCycle(cycle);


			if (j>0)
			{
				Node->getComponent<GridNodeComponent>().lock()->SetConnection(Direction::TopLeft, lastLayer[j - 1]);
			}
			if (j<lastLayer.size())
			{
				Node->getComponent<GridNodeComponent>().lock()->SetConnection(Direction::TopRight, lastLayer[j]);
			}
			currentLayer.push_back(Node->getComponent<GridNodeComponent>());
			nodes.push_back(Node->getComponent<GridNodeComponent>());
		}

		lastLayer = currentLayer;
		currentLayer.clear();

	}


	return std::make_pair(nodes,disks);
}
