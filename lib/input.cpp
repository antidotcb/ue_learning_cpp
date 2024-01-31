#include "input.h"

#include "utils.h"

#include <iostream>
#include <stdexcept>

namespace input {

int32_t enter_positive_value(const std::string &parameter)
{
  if (parameter.empty())
  {
    throw std::runtime_error("Title can't be empty");
  }

  int32_t value;
  bool valid_input;
  const auto title_parameter = utils::to_title(parameter);

  do
  {
    std::cout << "\nEnter " << parameter << ": ";
    std::cout.flush();

    std::cin >> value;
    std::cin.ignore();

    valid_input = value > 0;
    if (!valid_input)
    {
      std::cout << "\n" << title_parameter << " can't be zero or negative\n";
      std::cout.flush();
    }
  } while (!valid_input);

  return value;
}

int32_t enter_any_value(const std::string &parameter)
{
  if (parameter.empty())
  {
    throw std::runtime_error("Title can't be empty");
  }

  int32_t value;

  std::cout << "\nEnter " << parameter << ": ";
  std::cout.flush();

  std::cin >> value;
  std::cin.ignore();

  return value;
}

std::string enter_string(const std::string &title)
{
  std::string result;

  std::cout << "\nEnter " << title << ": ";
  std::cout.flush();

  std::cin >> result;
  std::cin.ignore();

  return result;
}

game::Class enter_class()
{
  bool valid_input;
  int32_t class_number;

  const auto &class_names = game::g_ClassNames;
  do
  {
    std::cout << "\nSelect class: \n";

    for (const auto &class_name: class_names)
    {
      std::cout << static_cast<int32_t>(class_name.first) << ". " << class_name.second << "\n";
    }
    std::cout << "Please enter number: ";
    std::cout.flush();

    std::cin >> class_number;
    std::cin.ignore();

    valid_input = std::find_if(class_names.begin(), class_names.end(),
                               [class_number](const auto &class_name) {
                                 return static_cast<int32_t>(class_name.first) == class_number;
                               })
               != class_names.end();
    if (!valid_input)
    {
      std::cout << "\nWrong class number\n";
      std::cout.flush();
    }
  } while (!valid_input);

  return static_cast<game::Class>(class_number);
}

} // namespace input
