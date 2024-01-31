#pragma once

#include "types.h"

#include <cstdint>
#include <string>


namespace input {

int32_t enter_positive_value(const std::string &parameter);

int32_t enter_any_value(const std::string &parameter);

std::string enter_string(const std::string &title);

game::Class enter_class();

} // namespace input
