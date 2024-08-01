#include "term-chart.hpp"

#include <iostream>
#include <string>

constexpr float linear(const float value)
{
	return value;
}

constexpr float exponential(const float value)
{
	return std::pow(value, 4);
}

constexpr float constant(const float value)
{
	return 1;
}

int main(void)
{
	constexpr int graph_height = 8;
	constexpr int value_count = 128;

	constexpr float wave_function_frequency = 0.05f;

	const auto wave_function = [wave_function_frequency](auto wave_function) -> std::vector<float>
	{
		std::vector<float> values;
		float value = 0;
		for (int i = 0; i < value_count; ++i)
		{
			values.emplace_back(wave_function(value));
			value += wave_function_frequency;
		}
		return values;
	};

	const auto graph = [graph_height, wave_function](const std::string& name, const auto function)
	{
		std::cout << name << '\n' << term_chart::render(graph_height, wave_function(function)) << '\n';
	};

	graph("sin", sin);
	graph("cos", cos);
	graph("tan", tan);
	graph("linear increase", linear);
	graph("exponential increase", exponential);
	graph("constant", constant);

	std::vector<int> custom_graph_values = { 0, 0, 0, 2, 5, 2, 2, 3, 3, 2, 6, 10, 11, 12, 12, 12, 12, 13, 14, 15, 15, 12, 12, 12, 9, 9, 9, 8, 8, 7, 7, 6, 5, 5, 4, 3, 2, 1, 0, -1, -5, -5, -4, 0, 1, 2, 3, 7, 9, 10, 12, 14, 14, 14, 14, 14, 14, 10, 9, 9, 8, 9, 11, 12, 7, 3, 0 };
	std::cout << "custom graph chars\n" << term_chart::render(graph_height, custom_graph_values, true, "o", ".");
}
