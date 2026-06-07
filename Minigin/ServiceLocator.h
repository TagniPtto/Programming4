#pragma once


namespace dae {

	template<typename T>
	class ServiceLocator final
	{
		static T* m_pInstance;
	public:
		static T& Get();
		static void Register(T* instance);
	public:
		ServiceLocator() = delete;
	};
	

	template<typename T>
	T& ServiceLocator<T>::Get() {
		return *m_pInstance;
	}
	template<typename T>
	void ServiceLocator<T>::Register(T* instance) {
		if (instance)
		{
			m_pInstance = instance;
		}
	}
	template<typename T>
	T* ServiceLocator<T>::m_pInstance = nullptr;
}
