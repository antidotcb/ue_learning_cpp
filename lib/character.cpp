#include "character.h"

#include "constants.h"
#include "input.h"
#include "utils.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

namespace game {

void print_character(const Character &result)
{
  const auto class_name_iter = std::find_if(g_ClassNames.begin(), g_ClassNames.end(), [&result](const auto &class_name) {
    return class_name.first == result.of_class;
  });
  assert(class_name_iter != g_ClassNames.end());
  if (class_name_iter == g_ClassNames.end())
  {
    throw std::runtime_error("Unknown character class");
  }

  std::cout << "Character\n";
  std::cout << "Name: " << result.name << "\n";
  std::cout << "Health: " << result.health << "\n";
  std::cout << "Class: " << class_name_iter->second << "\n";

  std::cout.flush();
}

Character create_character()
{
  std::cout << "* Character creation\n";

  const auto name = input::enter_string(g_Name);
  const auto health = input::enter_positive_value(g_Health);
  const auto power = input::enter_positive_value(g_Power);
  const auto class_type = input::enter_class();

  return Character{
    .name = name,
    .of_class = class_type,
    .max_health = health,
    .health = health,
    .power = power,
  };
}

int32_t apply_character_power(const Character &character, int32_t damage)
{
  if (character.of_class == Class::Mage)
  {
    if (damage > 2 * character.power)
    {
      const auto random_number = utils::get_random_number();
      if (random_number % 2 == 0)
      {
        damage = 0;
      }
    }
  }
  else if (character.of_class == Class::Warrior)
  {
    if (static_cast<float>(character.health) < 0.3f * static_cast<float>(character.max_health))
    {
      damage -= std::min(damage, character.power);
    }
  }
  return damage;
}

int32_t calc_damage(const Character &character, int32_t damage)
{
  if (character.of_class == Class::Mage)
  {
    if (damage % 2 == 0)
    {
      damage *= 2;
    }
  }
  else if (character.of_class == Class::Warrior)
  {
    if (damage % 2 == 1)
    {
      damage *= 3;
    }
    else
    {
      damage = 0;
    }
  }
  else
  {
    throw std::runtime_error("Unknown character class");
  }

  return damage;
}

int32_t apply_damage(const int32_t original_damage, const Character &character)
{
  const auto input_damage = calc_damage(character, original_damage);
  const auto actual_damage = apply_character_power(character, input_damage);
  const auto positive_damage = std::max<int32_t>(0, actual_damage);
  return std::min<int32_t>(character.health, positive_damage);
}

Character get_default_character()
{
  return Character{
    .name = "John Doe",
    .of_class = Class::Warrior,
    .max_health = 100,
    .health = 100,
    .power = 10,
  };
}

} // namespace game
