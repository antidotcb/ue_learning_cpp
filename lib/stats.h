#pragma once

#include "types.h"

#include <cstdint>
#include <optional>
#include <vector>

namespace utils {

class Stats
{
public:
  void add_damage(int32_t damage);

  [[nodiscard]] const std::vector<int32_t> &get_damage() const;

  [[nodiscard]] std::optional<int32_t> get_max_damage() const;

  [[nodiscard]] std::optional<int32_t> get_min_damage() const;

  [[nodiscard]] std::vector<size_t> get_damage_turns(int32_t damage) const;

  [[nodiscard]] std::vector<size_t> get_healing_turns() const;

  [[nodiscard]] bool no_damage() const;

  [[nodiscard]] int32_t total(game::DamageType damage_type) const;

private:
  std::vector<int32_t> damage_;
};

std::ostream &operator<<(std::ostream &out, const Stats &stats);

} // namespace utils
