#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	struct InputCommand
	{
		unsigned button;
		unsigned flag;
		Command* pCommand;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		void Destroy();
		/*bool IsPressed(unsigned button) const;*/
		void AddCommand(Command* pCommand, unsigned button, unsigned flag);
	private:
		using ControllerCommandsMap = std::vector<InputCommand>;
		ControllerCommandsMap m_Commands{};
		PXINPUT_KEYSTROKE m_Stroke{ new XINPUT_KEYSTROKE };
		XINPUT_STATE m_CurrentState{};
	};

}
