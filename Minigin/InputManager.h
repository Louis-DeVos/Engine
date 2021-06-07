#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{

	struct ControllerCommand
	{
		unsigned button;
		unsigned flag;
		Command* pCommand;
	};
	struct KeyboardCommand
	{
		int button;
		unsigned flag;
		Command* pCommand;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager() override;
		bool ProcessInput();
		void Destroy();
		void Clear();
		/*bool IsPressed(unsigned button) const;*/
		void AddControllerCommand(Command* pCommand, unsigned button, unsigned flag);
		void AddKeyboardCommand(Command* pCommand, int button, unsigned flag);
	private:
		using ControllerCommandsMap = std::vector<ControllerCommand>;
		ControllerCommandsMap m_ControllerCommands{};
		using KeyboardCommandsMap = std::vector<KeyboardCommand>;
		KeyboardCommandsMap m_KeyboardCommands{};
		PXINPUT_KEYSTROKE m_Stroke{ new XINPUT_KEYSTROKE };
		XINPUT_STATE m_CurrentState{};
	};

}
