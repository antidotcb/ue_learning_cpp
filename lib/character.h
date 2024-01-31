#pragma once

#include "types.h"

#include <cstdint>
#include <string>

namespace game {

struct Character
{
  std::string name{};
  Class of_class{Class::Warrior};
  int32_t max_health{};
  int32_t health{};
  int32_t power{};
};

int32_t apply_damage(int32_t original_damage, const Character &character);

void print_character(const Character &result);

[[maybe_unused]] Character get_default_character();
[[maybe_unused]] Character create_character();

} // namespace game
