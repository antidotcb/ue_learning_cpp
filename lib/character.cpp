#include "character.h"

#include "constants.h"
#include "input.h"
#include "utils.h"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>

namespace game {

int32_t Character::total_damage() const { return melee_damage + ranged_damage; }

std::ostream &operator<<(std::ostream &out, const Character &character)
{
  out << "Name: " << character.name << "\n";
  out << "Class: " << character.of_class << "\n";
  out << "Health: " << character.health << "\n";
  out << "Power: " << character.power << "\n";
  out << "Melee damage: " << character.melee_damage << "\n";
  out << "Ranged damage: " << character.ranged_damage << "\n";
  out << "Total damage: " << character.total_damage();

  return out;
}

bool operator<(const Character &lhs, const Character &rhs) { return lhs.total_damage() < rhs.total_damage(); }

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

Character create_random_character()
{
  static size_t character_counter = 0;
  character_counter++;

  const auto health = 50 + utils::get_random_number() % 10 * 10;

  return {
    .name = "Character #" + std::to_string(character_counter),
    .of_class = utils::get_random_number() % 2 ? Class::Warrior : Class::Mage,
    .max_health = health,
    .health = health,
    .power = utils::get_random_number(),
    .melee_damage = utils::get_random_number(),
    .ranged_damage = utils::get_random_number(),
  };
}

std::vector<game::Character> generate_characters(const size_t number_of_characters)
{
  std::vector<game::Character> result;
  result.reserve(number_of_characters);

  for (auto i = 0; i < number_of_characters; ++i)
  {
    result.emplace_back(game::create_random_character());
    std::cout << "\n" << result.back() << "\n";
  }

  return result;
}

} // namespace game
