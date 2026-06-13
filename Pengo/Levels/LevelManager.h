#pragma once
#include <vector>
#include <memory>
#include "Level.h"
#include <Singleton.h>

namespace pengo {
	class LevelManager final : public dae::Singleton<LevelManager>
	{
	public:
		~LevelManager() = default;
		void AddLevel(std::unique_ptr<Level> level); 
		void Load(int index);
	private:
		std::vector<std::unique_ptr<Level>> m_levels;
	};
}
