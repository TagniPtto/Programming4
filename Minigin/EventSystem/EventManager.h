#pragma once
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <memory>

#include "IObserver.h"
#include "Events/Event.h"

namespace dae {

	
//synchronous eventManager
	class EventManager final {
	private:
		std::queue<std::unique_ptr<Event>> EventQueue;
		std::unordered_map<EventId,std::vector<IObserver*>> Subscribers;

	private:
		EventManager();
	public:
		EventManager(const EventManager& other) = delete;
		EventManager(EventManager&& other) = delete;
		EventManager& operator=(const EventManager& other) = delete;
		EventManager& operator=(EventManager&& other) = delete;

		void SubscribeEvent(EventId type, IObserver* subscriber);
		void UnsubscribeEvent(EventId type,IObserver* subscriber);
		void SendEvent(std::unique_ptr<Event> event);

		void DispatchEvents();
		
	};
}