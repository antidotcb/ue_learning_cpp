#pragma once

#include "constants.h"

#include <array>
#include <cstdint>
#include <utility>

namespace game {

enum class Class : int8_t
{
  Mage = 1,
  Warrior = 2
};

const std::array<std::pair<Class, const char *>, 2> g_ClassNames{std::make_pair(Class::Mage, g_Mage),
                                                                 std::make_pair(Class::Warrior, g_Warrior)};

} // namespace game