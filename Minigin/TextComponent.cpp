#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(const std::string& text, Font* font, dae::GameObject* pGameObject)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font)
	, m_pGameObject{pGameObject}
{

}

dae::TextComponent::~TextComponent()
{
	delete m_Font;
}

void dae::TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}

		RenderComponent* pRenderComponent = m_pGameObject->getComponent<RenderComponent>();
		if (pRenderComponent != nullptr)
		{
			dae::Texture2D* pTexture = new dae::Texture2D(SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf));
			if (pTexture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			pRenderComponent->SetTexture(pTexture);
			m_NeedsUpdate = false;
		}
	}
}

void dae::TextComponent::FixedUpdate(float)
{

}

void dae::TextComponent::Render(const glm::vec3& ) const
{
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}



