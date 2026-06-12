#pragma once
#include <vector>
#include <memory>
#include "Level.h"

namespace pengo {
	class LevelManager final {
	private:
		LevelManager() = default;
	public:
		LevelManager(LevelManager&&) = delete;
		LevelManager(const LevelManager&) = delete;
		LevelManager& operator=(const LevelManager&) = delete;
		LevelManager& operator=(LevelManager&&) = delete;

		Load

	private:
		std::vector<std::unique_ptr<Level>> m_levels;
	};
}
