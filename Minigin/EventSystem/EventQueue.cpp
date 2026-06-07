#include "EventQueue.h"

void dae::EventQueue::SubscribeEvent(EventId type,IObserver* subscriber)
{
	m_Subscribers[type].push_back(subscriber);
}

void dae::EventQueue::UnsubscribeEvent(EventId type, IObserver* subscriber)
{
	m_Subscribers[type].erase(std::remove(m_Subscribers[type].begin(), m_Subscribers[type].end(), subscriber), m_Subscribers[type].end());
}

void dae::EventQueue::SendEvent(std::unique_ptr<Event> event)
{
	m_Queue.push(std::move(event));
}

void dae::EventQueue::DispatchEvents()
{
	while(m_Queue.size()) {
		auto event = std::move(m_Queue.front());
		m_Queue.pop();

		for (IObserver* subscriber : m_Subscribers[event->GetType()])
		{
			if (subscriber) 
			{
				subscriber->Notify(*event);
			}
		}
	}
}
