#include "lesson_16.h"

#include "character.h"
#include "input.h"
#include "utils.h"

#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace {
std::map<std::string, std::vector<game::Character>> clans;
} // namespace

int GetTotalStrength(const std::string &clan_name);

namespace {

enum class FightResult : int8_t
{
  Loss = -1,
  Draw = 0,
  Win = 1,
};

int to_score(const int fight_result)
{
  return fight_result == static_cast<int>(FightResult::Win) ? 3 : fight_result == static_cast<int>(FightResult::Draw) ? 1 : 0;
}

const char *to_string(const int fight_result)
{
  return fight_result == static_cast<int>(FightResult::Win) ? "win" : fight_result == static_cast<int>(FightResult::Draw) ? "draw" : "loss";
}

game::Character read_character()
{
  game::Character character;
  std::cout << "Enter player name: ";
  std::cin >> character.name;
  std::cout << "Enter player strength: ";
  std::cin >> character.melee_damage;
  return character;
}

bool ask_yes_no(const std::string &question)
{
  std::cout << "\n" << question << " (y/n): ";
  char answer{};
  std::cin >> answer;
  std::cin.ignore();
  return answer == 'y';
}

using Scores = std::vector<std::pair<std::string, size_t>>;

void print_player(const std::string &clan, const game::Character &character)
{
  std::cout << "\nCharacter: " << character.name << " with strength of " << character.melee_damage << " in clan " << std::quoted(clan);
}

void enter_manually()
{
  std::cout << "\nEnter players details";
  do
  {
    const auto clan = input::enter_string("clan");
    const auto character = read_character();
    clans[clan].push_back(character);
    std::cout << "\nPlayer added to clan " << std::quoted(clan) << " total players: " << GetPlayerCount(clan);
  } while (ask_yes_no("Do you want to enter another player?"));
}

void generate_automatically()
{
  constexpr size_t kNumberOfClans = 5;
  constexpr std::array<const char *, kNumberOfClans> kClanNames = {
    "Zero Clue Crew", "First Rate Raiders", "Too Cool Collective", "Thrice as Nice Knights", "Four Score Warriors",
  };

  clans.clear();
  for (auto &clan_name: kClanNames)
  {
    auto &clan = clans[clan_name];
    const auto number_of_players = 1u + utils::get_random_number(4u);
    clan.reserve(number_of_players);
    for (size_t i = 0; i < number_of_players; ++i)
    {
      const auto character = game::create_random_character();
      print_player(clan_name, character);
      clan.push_back(character);
    }
    std::cout << "\n";
  }
}

Scores simulate_fights()
{
  std::cout << "\n\nClan fight results:";
  std::unordered_map<std::string, size_t> clan_scores;
  for (const auto &clan: clans)
  {
    for (const auto &other_clan: clans)
    {
      if (clan.first != other_clan.first)
      {
        const auto fight_result = ClanFight(clan.first, other_clan.first);
        std::cout << "\n"
                  << std::quoted(clan.first) << " [" << GetTotalStrength(clan.first) << "] vs "                   //
                  << std::quoted(other_clan.first) << " [" << GetTotalStrength(other_clan.first) << "], result: " //
                  << to_string(fight_result);
        clan_scores[clan.first] += to_score(fight_result);
        clan_scores[other_clan.first] += fight_result < 0 ? to_score(-fight_result) : 0;
      }
    }
    std::cout << "\n";
  }

  Scores sorted_clan_scores(clan_scores.begin(), clan_scores.end());
  std::sort(sorted_clan_scores.begin(), sorted_clan_scores.end(), [](const auto &lhs, const auto &rhs) {
    return lhs.second > rhs.second;
  });
  return sorted_clan_scores;
}

void print_score_results(const Scores &clan_scores)
{
  std::cout << "\n\nClan scores:";
  for (const auto &clan_score: clan_scores)
  {
    const auto &clan_name = clan_score.first;
    const auto score = clan_score.second;
    std::cout << "\n - " << std::quoted(clan_name) << " with score: " << score;
  }
}

} // namespace

int GetTotalStrength(const std::string &clan_name)
{
  auto clan = clans.find(clan_name);
  if (clan == clans.end())
  {
    return 0;
  }

  return std::accumulate(clan->second.begin(), clan->second.end(), 0, [](int total, const game::Character &character) {
    return total + character.melee_damage;
  });
}

int GetPlayerCount(const std::string &clan_name)
{
  auto clan = clans.find(clan_name);
  if (clan == clans.end())
  {
    return 0;
  }

  return static_cast<int>(clan->second.size());
}

int ClanFight(const std::string &first_clan_name, const std::string &second_clan_name)
{
  const auto first_clan_strength = GetTotalStrength(first_clan_name);
  const auto second_clan_strength = GetTotalStrength(second_clan_name);

  // extra: if the difference of strength is less than 10% of total strength, the outcome of the fight is random (win or loss, 50/50 chance)
  {
    const auto difference = std::abs(first_clan_strength - second_clan_strength);
    const auto total_strength = static_cast<float>(first_clan_strength + second_clan_strength);
    const auto strength_ratio = static_cast<float>(difference) / total_strength;

    if (strength_ratio < 0.1f)
      return utils::get_random_number() % 2 == 0 ? static_cast<int>(FightResult::Win) : static_cast<int>(FightResult::Loss);
  }

  return first_clan_strength > second_clan_strength  ? static_cast<int>(FightResult::Win)
       : first_clan_strength == second_clan_strength ? static_cast<int>(FightResult::Draw)
                                                     : static_cast<int>(FightResult::Loss);
}

int lesson_16_task()
{
  const auto generate = ask_yes_no("Do you want to enter generate clans with players?");

  generate ? generate_automatically() : enter_manually();

  std::cout << "\nClans:";
  for (const auto &clan: clans)
  {
    const auto &clan_name = clan.first;
    std::cout << "\n - " << clan_name << " with " << GetPlayerCount(clan_name)
              << " players and total strength: " << GetTotalStrength(clan_name);
  }

  // some extra :) simple 2 fights each clan vs each other simulation and scores (3 for win, 1 for draw, 0 for loss)

  auto clan_scores = simulate_fights();
  print_score_results(clan_scores);
  std::cout << "\n\n";
  return 0;
}
