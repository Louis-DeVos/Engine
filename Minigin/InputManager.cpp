#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
	for (auto command : m_Commands)
	{
		delete command.pCommand;
	}
	delete m_Stroke;
}

bool dae::InputManager::ProcessInput()
{
	/*ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);*/

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}


	//PXINPUT_KEYSTROKE stroke = new XINPUT_KEYSTROKE;
	XINPUT_KEYSTROKE stroke{};
	auto result = XInputGetKeystroke(0, 0, m_Stroke);


	while (result == ERROR_SUCCESS)
	{
		for (auto inputCommand : m_Commands)
		{
			if (inputCommand.button == m_Stroke->VirtualKey && m_Stroke->Flags == inputCommand.flag)
			{
				inputCommand.pCommand->Execute();
			}
		}
		result = XInputGetKeystroke(0, 0, m_Stroke);
	}


	return true;
}

void dae::InputManager::Destroy()
{
	//for (auto command : m_Commands)
	//{
	//	delete command.pCommand;
	//}
}

void dae::InputManager::AddCommand(Command* pCommand, unsigned button, unsigned flag)
{
	m_Commands.push_back(InputCommand{ button, flag, pCommand });
}

//bool dae::InputManager::IsPressed(ControllerButton button) const
//{
//	switch (button)
//	{
//	case ControllerButton::ButtonA:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
//	case ControllerButton::ButtonB:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
//	case ControllerButton::ButtonX:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
//	case ControllerButton::ButtonY:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
//	default: return false;
//	}
//}

