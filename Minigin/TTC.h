#pragma once

#include <array>
#include <memory>

class TTC {

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
		GameObject3DAlt():transform(std::make_unique<Transform>()) {

		}
		std::unique_ptr<Transform> transform;
		int ID;

	};


	
public:
	static void Render();
	static std::array<float, 10> resultEx1;
	static std::array<float, 10> resultEx2;
	static std::array<float, 10> resultEx2Alt;

private:

	TTC() = default;
	static void SampleExercise1(int sampleAmount);
	static void SampleExercise2(int sampleAmount);
	static void SampleExercise2Alt(int sampleAmount);
	static void Exercise1();
	static void Exercise2();
	static void Exercise2Alt();

};
