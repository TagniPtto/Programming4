#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "IObserver.h"
#include "Event.h"

namespace dae {

	
//synchronous eventManager
	class EventManager final {
	private:
		std::vector<Event> EventQueue;
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
		void SentEvent(Event event);

		void DispatchEvents();
		
	};
}