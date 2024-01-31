#include "selector.h"

namespace game::character::selector {

std::optional<size_t> get_best(const std::vector<game::Character> &characters)
{
  if (characters.empty())
  {
    return std::nullopt;
  }

  return std::max_element(characters.begin(), characters.end()) - characters.begin();
}

std::map<game::Class, size_t> get_best_by_class(const std::vector<game::Character> &characters)
{
  std::map<game::Class, size_t> result;
  for (auto i = 0; i < characters.size(); ++i)
  {
    const auto character_class = characters[i].of_class;
    if (result.find(character_class) == result.end())
    {
      result[character_class] = i;
    }
    else
    {
      const auto best_character_index = result[character_class];
      if (characters[best_character_index] < characters[i])
      {
        result[character_class] = i;
      }
    }
  }

  return result;
}

} // namespace game::character::selector
