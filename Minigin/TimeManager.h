namespace dae {
	class Time {
	protected:
		float m_deltaTime{};
	public:
		static Time& Get() {
			static Time instance;
			return instance;
		}
		void Update(float t) {
			m_deltaTime = t;
		}
		float GetDeltaTime() {
			return m_deltaTime;
		}
	protected:
		Time() = default;
	};
}

