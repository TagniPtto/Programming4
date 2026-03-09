#pragma once

namespace dae {
	class GameObject;
}
class ObjectComponent
{

protected:
	dae::GameObject* m_owner;

protected:
	explicit ObjectComponent(dae::GameObject& owner);

public :
	virtual ~ObjectComponent() = default;

	ObjectComponent(ObjectComponent&& other) = delete;
	ObjectComponent(const ObjectComponent& other) = delete;

	ObjectComponent operator=(ObjectComponent&& other) = delete;
	ObjectComponent operator=(const ObjectComponent& other) = delete;

	virtual void Render() const {};
	virtual void RenderUI() {};
	virtual void Update() {};
	virtual void FixedUpdate(float) {};
};

