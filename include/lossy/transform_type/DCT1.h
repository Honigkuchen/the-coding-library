#pragma once

// C includes
#include <cmath>

// STL includes
#include <vector>

namespace cl::lossy::transform_type
{
class DCT1
{
public:
  template <typename T>
  [[nodiscard]] constexpr auto transform(const std::vector<T>& numbers) const
  {
    std::vector<T> result;

    for (std::size_t k = 0; k < numbers.size(); ++k)
    {
      const bool even = (k % 2) == 0;
      auto X_k = 1 / 2 * (numbers.front() + (even ? 1 : -1) * numbers.back());
      for (std::size_t n = 1; n != numbers.size() - 2; ++n)
        X_k += numbers[n] * std::cos(M_PI / (numbers.size() - 1) * n * k);
      result.push_back(X_k);
    }
    return result;
  }
};
} // namespace cl::lossy::transform_type