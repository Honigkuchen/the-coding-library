#include <benchmark/benchmark.h>
#include <coding_library/lossless/dictionary/byte_pair_coding/byte_pair_coding.hpp>

const std::string kString{
    "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW"
    "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW"};

static void
BM_BytePairCoding(benchmark::State& state)
{
  using cl::lossless::dictionary::BytePairCoding;

  using InputSymbolType = unsigned char;
  using OutputSymbolType = unsigned char;
  std::vector<InputSymbolType> symbols(kString.begin(), kString.end());
  BytePairCoding bpc;
  constexpr auto symbol_replacement_generator = []() -> OutputSymbolType
  {
    OutputSymbolType symbol_A_offset = 0;
    constexpr auto kMaxSymbolOffset = 26;
    if (symbol_A_offset == kMaxSymbolOffset)
      throw std::runtime_error("Cannot generate more symbols for byte pair encoding");
    const OutputSymbolType symbol = 'Z' - symbol_A_offset;
    symbol_A_offset += 1;
    return symbol;
  };

  for (auto _ : state)
    const auto code_symbols = bpc.Encode<InputSymbolType, OutputSymbolType>(symbols, symbol_replacement_generator);
}
BENCHMARK(BM_BytePairCoding);