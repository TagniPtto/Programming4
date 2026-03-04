

#include "TTC.h"

#include <vector>
#include <chrono>



#include <imgui.h>
#include <imgui_plot.h>


std::array<float, 10> TTC::resultEx1{};
std::array<float, 10> TTC::resultEx2{};
std::array<float, 10> TTC::resultEx2Alt{};


void TTC::Render()
{


	ImGui::Begin("Exercise1");
	if (ImGui::Button("Thrash the cach with int"))
	{
		SampleExercise1(10);
	}
	ImGui::PlotConfig conf1;
	conf1.values.xs = nullptr;
	conf1.values.ys = TTC::resultEx1.data();
	conf1.values.count = static_cast<int>(TTC::resultEx1.size());
	conf1.scale.min = 0.0f;
	conf1.scale.max = 10000.0f;
	conf1.tooltip.show = true;
	conf1.frame_size = ImVec2(400, 200);


	ImGui::Plot("plot1", conf1);
	ImGui::End();






	ImGui::Begin("Exercise2");
	if (ImGui::Button("Thrash the cach with Gameobject3d"))
	{
		SampleExercise2(10);
	}
	ImGui::PlotConfig conf2;
	conf2.values.xs = nullptr;
	conf2.values.ys = TTC::resultEx2.data();
	conf2.values.count = static_cast<int>(TTC::resultEx2.size());
	conf2.scale.min = 0.0f;
	conf2.scale.max = 10000.0f;
	conf2.tooltip.show = true;
	conf2.frame_size = ImVec2(400, 200);
	ImGui::Plot("plot2", conf2);

	if (ImGui::Button("Thrash the cach with Gameobject3dAlt"))
	{
		SampleExercise2Alt(10);
	}
	ImGui::PlotConfig conf3;
	conf3.values.xs = nullptr;
	conf3.values.ys = TTC::resultEx2Alt.data();
	conf3.values.count = static_cast<int>(TTC::resultEx2Alt.size());
	conf3.scale.min = 0.0f;
	conf3.scale.max = 10000.0f;
	conf3.tooltip.show = true;
	conf3.frame_size = ImVec2(400, 200);

	ImGui::Plot("plot3", conf3);

	ImGui::End();



}

void TTC::SampleExercise1(int sampleAmount)
{
	std::fill(TTC::resultEx1.begin(), TTC::resultEx1.end(), 0.f);
	for (int i = 0; i < sampleAmount; i++)
	{
		Exercise1();
	}
	for (int j = 0; j < 10; j++)
	{
		TTC::resultEx1[j] /= sampleAmount;
	}
}


void TTC::Exercise1()
{
	std::vector<int> arr(1000000);

	int index = 0;

	for (int stepsize = 1; stepsize < 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < arr.size(); i += stepsize)
		{
			arr[i] *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration<double, std::micro>(end - start);

		resultEx1[index++] += float(elapsed.count());
	}

}
void TTC::SampleExercise2(int sampleAmount)
{
	std::fill(TTC::resultEx2.begin(), TTC::resultEx2.end(),0.f);
	for (int i = 0; i < sampleAmount; i++)
	{
		Exercise2();
	}
	for (int j = 0; j < 10; j++)
	{
		TTC::resultEx2[j] /= sampleAmount;
	}
}



void TTC::Exercise2()
{
	std::vector<GameObject3D> arr(1000000);

	int index = 0;

	for (int stepsize = 1; stepsize < 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < arr.size(); i += stepsize)
		{
			arr[i].ID *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration<double, std::micro>(end - start);

		resultEx2[index++] += float(elapsed.count());
	}
}
void TTC::SampleExercise2Alt(int sampleAmount)
{
	std::fill(TTC::resultEx2Alt.begin(), TTC::resultEx2Alt.end(), 0.f);
	for (int i = 0; i < sampleAmount; i++)
	{
		Exercise2Alt();
	}
	for (int j = 0; j < 10; j++)
	{
		TTC::resultEx2Alt[j] /= sampleAmount;
	}
}
void TTC::Exercise2Alt()
{
	std::vector<GameObject3D> arr(1000000);

	int index = 0;

	for (int stepsize = 1; stepsize < 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < arr.size(); i += stepsize)
		{
			arr[i].ID *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration<double, std::micro>(end - start);

		resultEx2Alt[index++] += float(elapsed.count());
	}
}
