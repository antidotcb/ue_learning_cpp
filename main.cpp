#include "lib/character.h"
#include "lib/input.h"
#include "lib/selector.h"

#include <iostream>

int main()
{
  const auto number_of_characters = input::enter_positive_value("number of characters");

  const auto characters = game::generate_characters(number_of_characters);
  const auto best_in_class = game::character::selector::get_best_by_class(characters);

  for (const auto &best_character: best_in_class)
  {
    const auto &character = characters[best_character.second];
    std::cout << "\nBest character in " << best_character.first << " class: " << character.name << " with total "
              << character.melee_damage + character.ranged_damage << " attack";
  }

  const auto best_character_index = game::character::selector::get_best(characters);
  std::cout << "\nBest character: " << (best_character_index.has_value() ? characters[*best_character_index].name : "No characters");

  return 0;
}
