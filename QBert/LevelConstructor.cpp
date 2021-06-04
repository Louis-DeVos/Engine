#include "LevelConstructor.h"
#include "../Minigin/GameObject.h"
#include "../Minigin/RenderComponent.h"
#include "../Minigin/ResourceManager.h"
#include "../Minigin/Scene.h"
#include <fstream>
#include <regex>

LevelConstructor::LevelConstructor()
{
}

LevelConstructor::~LevelConstructor()
{
}

std::weak_ptr<GridNodeComponent> LevelConstructor::CreateLevel(dae::Scene& scene, std::string filePath) const
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


	std::shared_ptr<dae::GameObject> StartNode = std::make_shared<dae::GameObject>();
	auto render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(StartNode));
	render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Block_0.png"));
	StartNode->AddComponent(render);
	auto startNodeComp = std::make_shared<GridNodeComponent>(StartNode);
	StartNode->AddComponent(startNodeComp);
	StartNode->SetPosition(float(m_StartX), float(m_StartY));
	scene.Add(StartNode);

	startNodeComp->SetMaxState(maxState);
	startNodeComp->SetCycle(cycle);



	std::vector< std::weak_ptr<GridNodeComponent>> lastLayer{};
	std::vector< std::weak_ptr<GridNodeComponent>> currentLayer{};
	lastLayer.push_back(StartNode->getComponent<GridNodeComponent>());

	for (size_t i = 1; i < layers; i++)
	{
		for (size_t j = 0; j <= i; j++)
		{
			std::shared_ptr<dae::GameObject> Node = std::make_shared<dae::GameObject>();
			render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(Node));
			render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Block_0.png"));
			Node->AddComponent(render);
			auto nodeComp = std::make_shared<GridNodeComponent>(Node);
			Node->AddComponent(nodeComp);
			Node->SetPosition(m_StartX -m_SizeX/2.f*i + m_SizeX*j, m_StartY + m_SizeY*0.75f*i);
			scene.Add(Node);

			nodeComp->SetMaxState(maxState);
			nodeComp->SetCycle(cycle);


			if (j>0)
			{
				Node->getComponent<GridNodeComponent>().lock()->SetConnection(Position::TopLeft, lastLayer[j - 1]);
			}
			if (j<lastLayer.size())
			{
				Node->getComponent<GridNodeComponent>().lock()->SetConnection(Position::TopRight, lastLayer[j]);
			}
			currentLayer.push_back(Node->getComponent<GridNodeComponent>());
		}

		lastLayer = currentLayer;
		currentLayer.clear();

	}

	//std::shared_ptr<dae::GameObject> Node1 = std::make_shared<dae::GameObject>();
	//render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(Node1));
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Block_1.png"));
	//Node1->AddComponent(render);
	//Node1->AddComponent(std::make_shared<GridNodeComponent>(Node1));
	//Node1->SetPosition(304, 124);


	//std::shared_ptr<dae::GameObject> Node2 = std::make_shared<dae::GameObject>();
	//render = std::make_shared<RenderComponent>(std::weak_ptr<dae::GameObject>(Node2));
	//render->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Block_1.png"));
	//Node2->AddComponent(render);
	//Node2->AddComponent(std::make_shared<GridNodeComponent>(Node2));
	//Node2->SetPosition(336, 124);



	//Node1->getComponent<GridNodeComponent>().lock()->SetConnection(Position::TopRight, StartNode->getComponent<GridNodeComponent>());
	//Node2->getComponent<GridNodeComponent>().lock()->SetConnection(Position::TopLeft, StartNode->getComponent<GridNodeComponent>());


	//scene.Add(Node1);
	//scene.Add(Node2);



	return StartNode->getComponent<GridNodeComponent>();
}
