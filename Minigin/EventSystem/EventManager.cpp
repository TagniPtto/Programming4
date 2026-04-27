#include "EventManager.h"

void dae::EventManager::SubscribeEvent(EventId type,IObserver* subscriber)
{
	Subscribers[type].push_back(subscriber);
}

void dae::EventManager::UnsubscribeEvent(EventId type, IObserver* subscriber)
{
	Subscribers[type].erase(std::remove(Subscribers[type].begin(), Subscribers[type].end(), subscriber), Subscribers[type].end());
}

void dae::EventManager::SentEvent(Event event)
{
	EventQueue.push_back(event);
}

void dae::EventManager::DispatchEvents()
{
	for (Event& event : EventQueue) {
		for (IObserver* subscriber : Subscribers[event.id])
		{
			if (subscriber) 
			{
				subscriber->Notify(event);
			}
		}
	}
	EventQueue.clear();
}
