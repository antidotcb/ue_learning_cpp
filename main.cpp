#include <array>
#include <random>
#include <chrono>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <map>
#include <string>

enum class CharacterClass : int32_t {
    Mage = 1,
    Warrior = 2
};

struct Character {
    std::string name{};
    CharacterClass character_class{CharacterClass::Warrior};
    int32_t max_health{};
    int32_t health{};
    int32_t power{};
};

std::string to_title(const std::string &str) {
    if (str.empty()) {
        return str;
    }
    auto title = str;
    title.front() = static_cast<char>(toupper(title.front()));
    std::transform(std::next(title.begin()), title.end(), std::next(title.begin()), [](auto c) {
        return static_cast<char>(tolower(c));
    });
    return title;
}

namespace {
    // Parameters
    constexpr const char *const g_Name = "name";
    constexpr const char *const g_Health = "health";
    constexpr const char *const g_Power = "power";
    constexpr const char *const g_Damage = "damage";

    // Class names
    constexpr const char *const g_Mage = "Mage";
    constexpr const char *const g_Warrior = "Warrior";

    // Class names lookup
    const std::map<CharacterClass, std::string> g_ClassNames{
            {CharacterClass::Mage,    g_Mage},
            {CharacterClass::Warrior, g_Warrior}};
}// namespace

int32_t enter_value(const std::string &parameter) {
    if (parameter.empty()) {
        throw std::runtime_error("Title can't be empty");
    }

    int32_t value;
    bool valid_input;
    const auto title_parameter = to_title(parameter);

    do {
        std::cout << "Enter " << parameter << ": ";
        std::cout.flush();

        std::cin >> value;
        std::cin.ignore();

        valid_input = value > 0;
        if (!valid_input) {
            std::cout << title_parameter << " can't be zero or negative\n" << std::endl;
            std::cout.flush();
        }
    } while (!valid_input);


    return value;
}


std::string enter_string(const std::string &title) {

    std::string result;

    std::cout << "Enter " << title << ": ";
    std::cout.flush();

    std::cin >> result;
    std::cin.ignore();

    return result;
}

CharacterClass enter_class() {
    bool valid_input;
    int32_t class_number;
    do {
        std::cout << "Select class: " << "\n";
        for (const auto &class_name: g_ClassNames) {
            std::cout << static_cast<int32_t>(class_name.first) << ". " << class_name.second << "\n";
        }
        std::cout.flush();

        std::cin >> class_number;
        std::cin.ignore();

        valid_input = g_ClassNames.find(static_cast<CharacterClass>(class_number)) != g_ClassNames.end();
        if (!valid_input) {
            std::cout << "Wrong class number\n" << std::endl;
            std::cout.flush();
        }
    } while (!valid_input);

    return static_cast<CharacterClass>(class_number);
}

Character create_character() {
    std::cout << "* Character creation" << "\n";

    const auto name = enter_string(g_Name);
    const auto health = enter_value(g_Health);
    const auto power = enter_value(g_Power);
    const auto class_type = enter_class();

    Character result{.name = name,
            .character_class = class_type,
            .max_health = health,
            .health = health,
            .power = power,
    };

    std::cout << "Character created" << "\n";
    std::cout << "Name: " << result.name << "\n";
    std::cout << "Health: " << result.health << "\n";
    std::cout << "Class: " << g_ClassNames.at(result.character_class) << "\n";
    std::cout << std::endl;
    std::cout.flush();

    return result;
}

int32_t get_random_number() {
    static std::random_device device;
    std::mt19937 engine{device()};
    engine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int32_t> distribution{1, 100};
    return distribution(engine);
}

int32_t apply_character_power(const Character &character, int32_t damage) {
    if (character.character_class == CharacterClass::Mage) {
        if (damage > 2 * character.power) {
            const auto random_number = get_random_number();
            if (random_number % 2 == 0) {
                damage = 0;
            }
        }
    } else if (character.character_class == CharacterClass::Warrior) {
        if (static_cast<float>(character.health) < 0.3f * static_cast<float>(character.max_health)) {
            damage -= std::min(damage, character.power);
        }
    }
    return damage;
}

int32_t calc_damage(const Character &character, int32_t damage) {
    if (character.character_class == CharacterClass::Mage) {
        if (damage % 2 == 0) {
            damage *= 2;
        }
    } else if (character.character_class == CharacterClass::Warrior) {
        if (damage % 2 == 1) {
            damage *= 3;
        } else {
            damage = 0;
        }
    } else {
        throw std::runtime_error("Unknown character class");
    }

    return damage;
}

int32_t apply_damage(const int32_t original_damage, const Character &character) {
    const auto input_damage = calc_damage(character, original_damage);
    const auto actual_damage = apply_character_power(character, input_damage);
    const auto positive_damage = std::max<int32_t>(0, actual_damage);
    return std::min<int32_t>(character.health, positive_damage);
}

void game_loop(Character &character) {
    std::cout << "* Game loop" << "\n";
    do {
        const auto original_damage = enter_value(g_Damage);
        character.health -= apply_damage(original_damage, character);
        std::cout << "Health: " << character.health << "\n";
    } while (character.health > 0);

    std::cout << "Game over" << "\n";
}

int main() {
    auto character = create_character();
    game_loop(character);
    return 0;
}
