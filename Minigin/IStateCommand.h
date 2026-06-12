#pragma once

namespace dae
{
	class IStateCommand {
	public:
		virtual ~IStateCommand() = default;
		virtual void Execute() = 0;
	};
}