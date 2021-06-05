#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
	for (auto command : m_ControllerCommands)
	{
		delete command.pCommand;
	}
	for (auto command : m_KeyboardCommands)
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
		for (const auto& inputCommand : m_KeyboardCommands)
		{
			if (e.type == inputCommand.flag && e.key.keysym.sym == inputCommand.button)
			{
				//if(e.key.keysym.sym == SDL_Keycode)
				inputCommand.pCommand->Execute();
			}

		}
	}
	

	//PXINPUT_KEYSTROKE stroke = new XINPUT_KEYSTROKE;
	auto result = XInputGetKeystroke(0, 0, m_Stroke);


	while (result == ERROR_SUCCESS)
	{
		for (const auto& inputCommand : m_ControllerCommands)
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

void dae::InputManager::AddControllerCommand(Command* pCommand, unsigned button, unsigned flag)
{
	m_ControllerCommands.push_back(ControllerCommand{ button, flag, pCommand });
}

void dae::InputManager::AddKeyboardCommand(Command* pCommand, int button, unsigned flag)
{
	m_KeyboardCommands.push_back(KeyboardCommand{ button, flag, pCommand });
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

