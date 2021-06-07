#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include <string>
#include <stdexcept>

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, std::weak_ptr<dae::GameObject> pGameObject)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font)
	, m_pGameObject{pGameObject}
{

}

dae::TextComponent::~TextComponent()
{
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


		if (m_pRenderComponent.expired())
		{
			m_pRenderComponent = m_pGameObject.lock()->getComponent<RenderComponent>();
		}

		if (!m_pRenderComponent.expired())
		{
			std::shared_ptr<dae::Texture2D> pTexture = std::make_shared<dae::Texture2D>(SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf));
			if (pTexture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			m_pRenderComponent.lock()->SetTexture(pTexture);
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



