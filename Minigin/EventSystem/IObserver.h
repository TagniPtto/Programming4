#pragma once

namespace dae {

	struct Event;
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Notify(Event& event) = 0;
	};
}
