#include "MenuComponent.h"
#include "GameObject.h"
#include <memory>
#include "../3rdParty/imgui-1.81/imgui.h" 
#include "GameManagerComponent.h" 

MenuComponent::MenuComponent(std::weak_ptr<dae::GameObject> pGameObject, std::weak_ptr<GameManagerComponent> pManager)
	:m_pGameObject{pGameObject}
	,m_pGameManager{pManager}
{

}

MenuComponent::~MenuComponent()
= default;

void MenuComponent::Update(float )
{
}

void MenuComponent::FixedUpdate(float )
{
}

void MenuComponent::Render(const glm::vec3& ) const
{
	bool show = true;
	ImGui::Begin("window", &show);
	if (ImGui::Button("single player", { 100,30 }))
	{
		m_pGameManager.lock()->StartSinglePlayer();
	}
	if (ImGui::Button("co-op", { 100,30 }))
	{
		m_pGameManager.lock()->StartCoop();
	}
	if (ImGui::Button("versus", { 100,30 }))
	{
		m_pGameManager.lock()->StartVersus();
	}
	ImGui::SetWindowSize("window", { 120,150 });
	ImGui::End();



}
