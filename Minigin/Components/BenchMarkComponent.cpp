#include "BenchMarkComponent.h"


#include <chrono>
#include <algorithm>
#include <numeric>
#include <utility>


#include <imgui.h>
#include <imgui_plot.h>


dae::BenchMarkComponent::BenchMarkComponent(dae::GameObject& owner):
	ObjectComponent(owner), xData{}, resultEx1{}, resultEx2{}, resultEx2Alt{}
{
}


void dae::BenchMarkComponent::RenderUI()
{
	ImGui::Begin("Exercise1");
	if (ImGui::Button("Thrash the cache with int"))
	{
		SampleExercise(0, 10);
	}
	ImGui::PlotConfig conf1;
	conf1.values.xs = nullptr;
	conf1.values.ys = resultEx1.data();
	conf1.values.count = static_cast<int>(resultEx1.size());
	conf1.scale.min = 0.0f;
	conf1.scale.max = 10000.0f;
	conf1.tooltip.show = true;
	conf1.frame_size = ImVec2(400, 200);


	ImGui::Plot("plot1", conf1);
	ImGui::End();



	ImGui::Begin("Exercise2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Thrash the cach with Gameobject3d"))
	{
		SampleExercise(1, 10);
	}
	if (ImGui::Button("Thrash the cach with Gameobject3dAlt"))
	{
		SampleExercise(2, 10);
	}

	const float* y_data[] = { resultEx2.data(), resultEx2Alt.data() };
	static ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };
	static uint32_t selection_start = 0, selection_length = 0;


	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = xData.data();
	conf.values.count = int(xData.size());
	conf.values.ys_list = y_data;
	conf.values.ys_count = 2;
	conf.values.colors = colors;
	conf.grid_x.show = true;
	conf.grid_x.size = 128;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.scale.min = 0.0f;
	conf.scale.max = 10000.0f;
	conf.tooltip.show = true;
	conf.frame_size = ImVec2(400, 200);
	ImGui::Plot("plot2", conf);

	ImGui::End();
}


void dae::BenchMarkComponent::SampleExercise(int index,int amount)
{
	std::array<float, 10>* result = nullptr;
	for (int i{}; i < amount; i++) {
		switch (index)
		{
			case 0:
				Exercise1();
				result = &resultEx1;
				break;

			case 1: 
				Exercise2<GameObject3D>();
				result = &resultEx2;
				break;

			case 2:
				Exercise2<GameObject3DAlt>();
				result = &resultEx2Alt;
				break;
		default:
			return;
		}

	}

	int i{};
	for (std::vector<float>& resultVec : temp) {
		if (resultVec.size() > 0) {
			auto [minIt,maxIt] = std::minmax_element(resultVec.begin(), resultVec.end());

			float min_val = *minIt;
			float max_val = *maxIt;
			resultVec.erase(std::remove(resultVec.begin(), resultVec.end(), min_val), resultVec.end());
			resultVec.erase(std::remove(resultVec.begin(), resultVec.end(), max_val), resultVec.end());

			(*result)[i] = std::accumulate(resultVec.begin(), resultVec.end(), 0.0f) / resultVec.size();

			resultVec.clear();
			i++;
		}

	}
	
}
 void dae::BenchMarkComponent::Exercise1()
{
	std::vector<int> arr(1000000);
	//TODO make container last throughout all sample for memory allocation efficientcy this is an exercise about cache not memory alloc
	int index = 0;

	for (int stepsize = 1; stepsize < 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < int(arr.size()); i += stepsize)
		{
			arr[i] *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration<double, std::micro>(end - start);
		xData[index] = float(stepsize);
		temp[index].push_back(float(elapsed.count()));
		index++;
	}

}

template<typename T>
	requires std::is_same<T, dae::BenchMarkComponent::GameObject3D>::value || std::is_same<T,dae::BenchMarkComponent::GameObject3DAlt>::value
void dae::BenchMarkComponent::Exercise2()
{
	std::vector<T> arr(1000000);

	int index = 0;

	for (int stepsize = 1; stepsize < 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < int(arr.size()); i += stepsize)
		{
			arr[i].ID *= 2;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration<double, std::micro>(end - start);
		xData[index] = float(stepsize);
		temp[index].push_back(float(elapsed.count()));
		index++;
	}
}
