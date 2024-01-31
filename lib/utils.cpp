#include "utils.h"

#include <chrono>
#include <random>

namespace utils {

std::string to_title(const std::string &str)
{
  if (str.empty())
  {
    return str;
  }
  auto title = str;
  title.front() = static_cast<char>(toupper(title.front()));
  std::transform(std::next(title.begin()), title.end(), std::next(title.begin()), [](auto c) {
    return static_cast<char>(tolower(c));
  });
  return title;
}

int32_t get_random_number()
{
  static std::random_device device;
  std::mt19937 engine{device()};
  engine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int32_t> distribution{1, 100};
  return distribution(engine);
}

} // namespace utils
