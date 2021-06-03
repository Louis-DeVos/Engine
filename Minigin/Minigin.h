#pragma once
#include "MiniginLibType.h"
struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		virtual void Initialize();
		virtual void LoadGame() const;
		virtual void Cleanup();
		MINIGIN_ENTRY virtual void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	protected:
		SDL_Window* m_Window{};
	};
}