#pragma once

#include <Components/ObjectComponent.h>


namespace pengo {
	class MenuStateComponent : public dae::ObjectComponent {
		explicit MenuStateComponent(class dae::GameObject& owner);
	};
}
