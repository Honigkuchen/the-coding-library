// STL includes
#include <iostream>
#include <chrono>

// Project includes
#include <huffman.h>
#include <binary_number.h>

int main()
{
	{
		auto mean_ns = std::chrono::nanoseconds::zero();
		auto mean_us = std::chrono::microseconds::zero();
		auto mean_ms = std::chrono::milliseconds::zero();
		auto mean_s = std::chrono::seconds::zero();

		const std::string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
		const std::vector<char> message(s.begin(), s.end());

		huffman::Table<char> table;

		constexpr auto benchmark_runs = 1000;

		for (auto i = 0; i < benchmark_runs; ++i)
		{
			const auto start = std::chrono::system_clock::now();
			table = huffman::Encode(message);
			const auto end = std::chrono::system_clock::now();

			const auto elapsed = end - start;

			mean_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);
			mean_us += std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
			mean_ms += std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
			mean_s += std::chrono::duration_cast<std::chrono::seconds>(elapsed);
		}

		mean_ns /= benchmark_runs;
		mean_us /= benchmark_runs;
		mean_ms /= benchmark_runs;
		mean_s /= benchmark_runs;

		auto& output_stream = std::cout;

		table.PrintOn(output_stream);

		output_stream << std::endl;
		output_stream << "Mean duration: " << mean_ns.count() << "ns" << std::endl;
		output_stream << "Mean duration: " << mean_us.count() << "us" << std::endl;
		output_stream << "Mean duration: " << mean_ms.count() << "ms" << std::endl;
		output_stream << "Mean duration: " << mean_s.count() << "s" << std::endl;
	}
    return 0;
}
