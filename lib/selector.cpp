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
    const auto &character = characters[i];
    const auto character_class = character.of_class;
    if (result.find(character_class) == result.end())
    {
      result[character_class] = i;
      continue;
    }

    const auto best_character_index = result[character_class];
    const auto &best_character = characters[best_character_index];

    if (best_character < character)
    {
      result[character_class] = i;
    }
  }

  return result;
}

} // namespace game::character::selector
