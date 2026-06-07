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
	class EventQueue {
	private:
		std::queue<std::unique_ptr<Event>> m_Queue;
		std::unordered_map<EventId,std::vector<IObserver*>> m_Subscribers;
		
	private:
		friend class Minigin;
		EventQueue() = default;
	
	public:
		EventQueue(const EventQueue& other) = delete;
		EventQueue(EventQueue&& other) = delete;
		EventQueue& operator=(const EventQueue& other) = delete;
		EventQueue& operator=(EventQueue&& other) = delete;

		void SubscribeEvent(EventId type, IObserver* subscriber);
		void UnsubscribeEvent(EventId type,IObserver* subscriber);
		void SendEvent(std::unique_ptr<Event> event);

		void DispatchEvents();
		
	};
}