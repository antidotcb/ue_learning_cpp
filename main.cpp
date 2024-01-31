#include "lib/character.h"
#include "lib/input.h"

#include <iostream>

namespace game {

void loop(Character &character)
{
  std::cout << "\n* Game loop";

  do
  {
    const auto original_damage = input::enter_positive_value(g_Damage);

    const auto damage = apply_damage(original_damage, character);
    std::cout << "Actual damage: " << damage;

    character.health -= damage;
    std::cout << "\nHealth: " << character.health;
  } while (character.health > 0);

  std::cout << "\nGame over\n";
  std::cout.flush();
}

} // namespace game

int main()
{
  auto character = game::create_character();
  game::print_character(character);
  game::loop(character);
  return 0;
}
