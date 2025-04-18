#include <benchmark/benchmark.h>
#include <coding_library/lossless/other/run_length_coding/run_length_coding.hpp>

const std::string kString{
    "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW"
    "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW"};

static void
BM_RunLengthCoding(benchmark::State& state)
{
  const std::vector<char> symbols(kString.begin(), kString.end());
  using cl::lossless::other::RunLengthCoding;

  RunLengthCoding<char> rlc;

  for (auto _ : state)
    RunLengthCoding<char>::ResultType code_symbols = rlc.Encode(symbols);
}
BENCHMARK(BM_RunLengthCoding);