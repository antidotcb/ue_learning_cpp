#include "lib/character.h"
#include "lib/input.h"
#include "lib/stats.h"

#include <iostream>

namespace game {

void loop(Character &character)
{
  std::cout << "\n* Game loop";
  utils::Stats stats;

  do
  {
    const auto original_damage = input::enter_positive_value(g_Damage);

    if (original_damage > 0)
    { // Damage
      const auto damage = apply_damage(original_damage, character);
      std::cout << "Actual damage: " << damage;
      character.health -= damage;
      stats.add_damage(damage);
    }
    else
    { // Healing
      character.health -= original_damage;
      stats.add_damage(original_damage);
    }

    std::cout << "\nHealth: " << character.health;
  } while (character.health > 0);

  std::cout << "\n\nGame statistics\n" << stats;

  std::cout << "\nGame over\n";
  std::cout.flush();
}

} // namespace game

int main()
{
  auto character = game::get_default_character();
  std::cout << "Character\n" << character;
  game::loop(character);
  return 0;
}
