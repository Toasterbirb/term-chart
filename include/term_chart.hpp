#include <algorithm>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <type_traits>

namespace term_chart
{
	/**
	 * @brief Draw a line chart
	 *
	 * @tparam T value type
	 * @param height Amount of lines used for the chart
	 * @param values Y-values for the chart
	 * @param fill_area Fill the area below the chart line
	 * @param line_char Character(s) used for drawing the line
	 * @param background_char Character(s) used for drawing the background
	 */
	template<typename T>
	std::string render(const short height, const std::vector<T>& values, const bool fill_area = false, const std::string& line_char = "▀", const std::string& background_char = "▒")
	{
		static_assert(std::is_arithmetic<T>(), "only arithmetic types are supported");

		assert(height > 0);
		assert(values.size() > 2);

		std::vector<T> normalized_values( values.size() );

		const T min_value = *std::min_element(values.begin(), values.end());
		const T max_value = *std::max_element(values.begin(), values.end());

		if (min_value == max_value)
		{
			// All of the values are the same, so we can just create a straight line
			std::fill(normalized_values.begin(), normalized_values.end(), height * 0.5f);
		}
		else
		{
			const auto normalize = [](const T value, const T min, const T max, const short normalized_maximum)
			{
				return ((value - min) / static_cast<double>(max - min)) * normalized_maximum;
			};

			// Normalize the values normally
			std::transform(values.begin(), values.end(), normalized_values.begin(), [height, min_value, max_value, normalize](const T value){
				return std::round(normalize(value, min_value, max_value, height));
			});
		}

		std::string chart;

		// Render the chart into a string from bottom up
		for (short i = height; i > -1; --i)
		{
			for (size_t j = 0; j < normalized_values.size(); ++j)
			{
				if ((normalized_values[j] != i && !fill_area) || (normalized_values[j] < i && fill_area))
				{
					chart += background_char;
					continue;
				}

				chart += line_char;
			}

			chart += '\n';
		}

		return chart;
	}
}
