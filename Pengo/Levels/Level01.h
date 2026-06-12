#include "Level.h"

namespace pengo {
	class Level01 : public Level{
	public:
		~Level01() = default;
		void Load(dae::Scene& scene , GameMode mode);
	};
}