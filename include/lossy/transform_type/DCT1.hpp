#pragma once

// C includes
#include <cmath>

// STL includes
#include <type_traits>
#include <vector>

namespace cl::lossy::transform_type
{
class DCT1
{
private:
  /**
   * @brief Returns 1.0 if w is 0, otherwise this function returns 1/sqrt(2) as double.
   */
  template <typename T, typename = std::enable_if_t<std::is_unsigned_v<T>>>
  [[nodiscard]] constexpr double Alpha(const T& w) const
  {
    if (w == 0)
      return 1.0 / std::sqrt(2.0);
    return 1.0;
  }

public:
  template <std::size_t X, std::size_t Y, typename Predicate, typename T, typename = std::enable_if_t<std::is_default_constructible_v<T>>>
  [[nodiscard]] constexpr auto Transform(const T& numbers, Predicate p) const
  {
    T result = {};
    if (numbers.empty())
      return result;
    for (std::size_t u = 0; u != X; ++u)
    {
      const auto alpha_u = Alpha(u);
      for (std::size_t v = 0; v != Y; ++v)
      {
        const auto alpha_v = Alpha(v);
        double G_u_v = (1.0 / 4.0) * alpha_u * alpha_v;
        double sum = 0;
        for (std::size_t x = 0; x != X; ++x)
          for (std::size_t y = 0; y != Y; ++y)
            sum += p(numbers, x, y) * std::cos((2.0 * static_cast<double>(x) + 1.0) / 16.0 * static_cast<double>(u) * M_PI) * std::cos((2.0 * static_cast<double>(y) + 1.0) / 16.0 * static_cast<double>(v) * M_PI);

        p(result, u, v) = G_u_v * sum;
      }
    }
    return result;
  }
};
} // namespace cl::lossy::transform_type