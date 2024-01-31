#pragma once

#include "constants.h"

#include <array>
#include <cstdint>
#include <utility>
#include <ostream>

namespace game {

enum class DamageType : int8_t
{
  Healing = -1,
  NoDamage = 0,
  Damage = 1
};

enum class Class : int8_t
{
  Mage = 1,
  Warrior = 2
};

const std::array<std::pair<Class, const char *>, 2> g_ClassNames{std::make_pair(Class::Mage, g_Mage),
                                                                 std::make_pair(Class::Warrior, g_Warrior)};

const char *to_string(const Class &character_class);

std::ostream &operator<<(std::ostream &out, const Class &character_class);

} // namespace game
