#pragma once

#include "types.h"

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace game {

struct Character
{
  std::string name{};
  Class of_class{Class::Warrior};
  int32_t max_health{};
  int32_t health{};
  int32_t power{};
  int32_t melee_damage{};
  int32_t ranged_damage{};

  [[nodiscard]] int32_t total_damage() const;
};

std::ostream &operator<<(std::ostream &out, const Character &character);
bool operator<(const game::Character &lhs, const game::Character &rhs);

int32_t apply_damage(int32_t original_damage, const Character &character);

[[maybe_unused]] Character get_default_character();
[[maybe_unused]] Character create_character();
[[maybe_unused]] Character create_random_character();

std::vector<game::Character> generate_characters(size_t number_of_characters);

} // namespace game
