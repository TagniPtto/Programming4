#pragma once


#include <memory>
#include <array>
#include <vector>
#include "ObjectComponent.h"



namespace dae {


	class BenchMarkComponent : public ObjectComponent {


		struct Transform
		{
			float matrix[16] = {
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };
		};
		class GameObject3D
		{

		public:
			GameObject3D() = default;
			Transform transform;
			int ID;

		};
		class GameObject3DAlt
		{

		public:
			GameObject3DAlt() :transform(std::make_unique<Transform>()), ID{} {}
			std::unique_ptr<Transform> transform;
			int ID;

		};

	public:
		explicit BenchMarkComponent(dae::GameObject& owner);
		void RenderUI() override;

	private:


		void SampleExercise(int index,int amount);
		void Exercise1();
		template<typename T>
			requires std::is_same<T, dae::BenchMarkComponent::GameObject3D>::value || std::is_same<T, dae::BenchMarkComponent::GameObject3DAlt>::value
		void Exercise2();
		std::array<std::vector<float>, 10> temp;

		std::array<float, 10> xData;
		std::array<float, 10> resultEx1;
		std::array<float, 10> resultEx2;
		std::array<float, 10> resultEx2Alt;
		
	};


}