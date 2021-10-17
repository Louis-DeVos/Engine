#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


InputManager::~InputManager()
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

bool InputManager::ProcessInput()
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

void InputManager::Destroy()
{
	//for (auto command : m_Commands)
	//{
	//	delete command.pCommand;
	//}
}

void InputManager::Clear()
{
	for (auto command : m_KeyboardCommands)
	{
		delete command.pCommand;
	}
	for (auto command : m_ControllerCommands)
	{
		delete command.pCommand;
	}

	m_KeyboardCommands.clear();
	m_ControllerCommands.clear();
}



void InputManager::AddControllerCommand(Command* pCommand, unsigned button, unsigned flag)
{
	m_ControllerCommands.push_back(ControllerCommand{ button, flag, pCommand });
}

void InputManager::AddKeyboardCommand(Command* pCommand, int button, unsigned flag)
{
	m_KeyboardCommands.push_back(KeyboardCommand{ button, flag, pCommand });
}

//bool InputManager::IsPressed(ControllerButton button) const
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

