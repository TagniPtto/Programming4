#pragma once
#include <nlohmann/json.hpp>


#define REGISTER_COMPONENT(TYPE) \
dae::ComponentFactory::Get().Register( \
	#TYPE, \
	[](dae::GameObject& owner, const nlohmann::json& data)->void\
	{\
		dae::ObjectComponent* comp = owner.AddComponent<TYPE>(); \
		comp->Deserialize(data);\
	}\
	)


namespace dae {
	class GameObject;

	class ObjectComponent
	{
	private:
		dae::GameObject* m_owner;

	protected:
		explicit ObjectComponent(dae::GameObject& owner);

	public:
		virtual ~ObjectComponent() = default;

		ObjectComponent(ObjectComponent&& other) = delete;
		ObjectComponent(const ObjectComponent& other) = delete;

		ObjectComponent operator=(ObjectComponent&& other) = delete;
		ObjectComponent operator=(const ObjectComponent& other) = delete;


		dae::GameObject* GetOwner() const;

		virtual void Render() const;
		virtual void RenderUI();
		virtual void Update();
		virtual void FixedUpdate(float);

		virtual void Deserialize(const nlohmann::json& data);
		virtual void Serialize(nlohmann::json& data) const;
	};
}


