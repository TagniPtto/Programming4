#include "IObserver.h"
#include <vector>


namespace dae {
	struct Event;
	class Subject {

	private:
		std::vector<IObserver*> m_observers{};
	public:
		virtual ~Subject() = default;
		virtual void NotifyObservers(Event& event);

		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* observer);
	};
}