#pragma once
#include "GameMode.h"
#include <ServiceLocator.h>
#include <SceneSystem/SceneManager.h>
#include <SceneSystem/Scene.h>

namespace pengo
{
	class Level {	
	public:
		virtual ~Level() = default;
		virtual void Load(dae::Scene& scene, GameMode mode = GameMode::SinglePlayer) = 0;
	};
}