#pragma once
#include <functional>
#include <map>

#include <nlohmann/json.hpp>

#include "GameObject.h"

namespace dae {
	class PrefabFactory
	{
	public:
		static PrefabFactory& Get() {
			static PrefabFactory instance;
			return instance;
		}
		void CreatePrefab(std::string name, const nlohmann::json&);
	
	private:
		PrefabFactory();
	};
}