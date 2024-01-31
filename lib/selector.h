#pragma once

#include "character.h"

#include <map>
#include <optional>
#include <vector>

namespace game::character::selector {

std::optional<size_t> get_best(const std::vector<game::Character> &characters);

std::map<game::Class, size_t> get_best_by_class(const std::vector<game::Character> &characters);

} // namespace game::character::selector
