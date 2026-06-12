#pragma once

#include "TimeManager.h"
#include "InputSystem/InputTypes.h"

namespace dae{
	class IInputCommand {
	public:
		virtual ~IInputCommand() = default;
		virtual void Execute(dae::InputContext context) = 0;
	};
}