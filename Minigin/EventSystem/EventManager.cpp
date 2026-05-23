#include "EventManager.h"

void dae::EventManager::SubscribeEvent(EventId type,IObserver* subscriber)
{
	Subscribers[type].push_back(subscriber);
}

void dae::EventManager::UnsubscribeEvent(EventId type, IObserver* subscriber)
{
	Subscribers[type].erase(std::remove(Subscribers[type].begin(), Subscribers[type].end(), subscriber), Subscribers[type].end());
}

void dae::EventManager::SendEvent(std::unique_ptr<Event> event)
{
	EventQueue.push(std::move(event));
}

void dae::EventManager::DispatchEvents()
{
	while(EventQueue.size()) {
		auto event = std::move(EventQueue.front());
		EventQueue.pop();

		for (IObserver* subscriber : Subscribers[event->GetType()])
		{
			if (subscriber) 
			{
				subscriber->Notify(*event);
			}
		}
	}
}
