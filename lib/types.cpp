#include "types.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace game {

const char *to_string(const Class &character_class)
{
  const auto class_name_iter = std::find_if(g_ClassNames.begin(), g_ClassNames.end(), [character_class](const auto &class_name) {
    return class_name.first == character_class;
  });
  assert(class_name_iter != g_ClassNames.end());
  if (class_name_iter == g_ClassNames.end())
  {
    throw std::runtime_error("Unknown character class");
  }
  const auto &class_name = class_name_iter->second;
  return class_name;
}

std::ostream &operator<<(std::ostream &out, const Class &character_class)
{
  out << to_string(character_class);
  return out;
}

} // namespace game
