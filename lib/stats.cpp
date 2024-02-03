#include "stats.h"

#include <algorithm>
#include <limits>
#include <numeric>
#include <ostream>
#include <string>

namespace utils {

using DamageType = game::DamageType;

namespace {

DamageType damage_type(const int32_t damage)
{
  return damage == 0 ? DamageType::NoDamage : damage > 0 ? DamageType::Damage : DamageType::Healing;
}

std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &damage_turns)
{
  for (const auto index: damage_turns)
  {
    out << index << " ";
  }
  return out;
}

} // namespace

void Stats::add_damage(const int32_t damage) { damage_.push_back(damage); }

const std::vector<int32_t> &Stats::get_damage() const { return damage_; }

std::vector<size_t> Stats::get_healing_turns() const
{
  std::vector<size_t> result;
  for (size_t i = 0; i < damage_.size(); ++i)
  {
    if (damage_type(damage_[i]) == DamageType::Healing)
    {
      result.push_back(i + 1);
    }
  }

  return result;
}

bool Stats::no_damage() const
{
  auto zero_damage = [](const auto damage) {
    return damage == 0;
  };
  return std::any_of(damage_.begin(), damage_.end(), zero_damage);
}

int32_t Stats::total(const DamageType type) const
{
  return std::accumulate(damage_.begin(), damage_.end(), 0, [type](const auto sum, const auto damage) {
    return sum + (damage_type(damage) == type ? std::abs(damage) : 0);
  });
}

std::optional<int32_t> Stats::get_max_damage() const
{
  const auto max_damage = std::max_element(damage_.begin(), damage_.end());
  return max_damage != damage_.end() ? std::optional<int32_t>{*max_damage} : std::nullopt;
}

std::optional<int32_t> Stats::get_min_damage() const
{
  auto result = std::numeric_limits<int32_t>::max();
  for (const auto damage: damage_)
  {
    if (damage_type(damage) == DamageType::Damage)
    {
      result = std::min(result, damage);
    }
  }
  return result;
}

std::vector<size_t> Stats::get_damage_turns(const int32_t damage) const
{
  std::vector<size_t> result;
  for (size_t i = 0; i < damage_.size(); ++i)
  {
    if (damage_[i] == damage)
    {
      result.push_back(i + 1);
    }
  }

  return result;
}

std::ostream &operator<<(std::ostream &out, const Stats &stats)
{
  const auto &damage_ = stats.get_damage();
  out << "\nDamage table: \n";
  for (auto i = 0; i < damage_.size(); ++i)
  {
    out << i + 1 << " " << damage_[i] << "\n";
  }
  out << "\n";

  const auto max_damage = stats.get_max_damage();
  const auto min_damage = stats.get_min_damage();

  out << "\nMax Damage: " << (max_damage.has_value() ? std::to_string(max_damage.value()) : "N/A");
  if (max_damage.has_value())
  {
    out << " at turns: " << stats.get_damage_turns(max_damage.value());
  }

  out << "\nMin Damage: " << (min_damage.has_value() ? std::to_string(min_damage.value()) : "N/A");
  if (min_damage.has_value())
  {
    out << " at turns: " << stats.get_damage_turns(min_damage.value());
  }
  const auto total_healing = stats.total(DamageType::Healing);
  out << "\nTotal Healing: " << total_healing;
  if (total_healing > 0)
  {
    out << " at turns: " << stats.get_healing_turns();
  }

  const auto total_damage = stats.total(DamageType::Damage);
  out << "\nTotal Damage: " << total_damage;

  const auto no_damage_present = stats.no_damage();
  out << "\nNo Damage Present: " << (no_damage_present ? "Yes" : "No") << "\n";

  return out;
}

} // namespace utils
