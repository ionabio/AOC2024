module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

export module Day3;

namespace Day3 {
auto matchStringForPartOne(const auto &input) {
  auto valuePart1 = 0;
  auto mulPattern = std::regex(R"(mul\((\d+),(\d+)\))");
  auto matches_begin =
      std::sregex_iterator(input.begin(), input.end(), mulPattern);
  auto matches_end = std::sregex_iterator();
  for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
    auto match = *i;
    auto num1 = std::stoi(match.str(1));
    auto num2 = std::stoi(match.str(2));
    valuePart1 += num1 * num2;
  }
  return valuePart1;
}

auto matchStringForPartTwo(const auto &input, auto& enabled) {
  auto valuePart2 = 0;
  auto mulPart2Pattern = std::regex(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
  auto matches_begin =
      std::sregex_iterator(input.begin(), input.end(), mulPart2Pattern);
  auto matches_end = std::sregex_iterator();
  for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
    auto match = *i;
    auto str = match.str(0);
    if (str == "do()") {
      enabled = true;
    }else if (str == "don't()") {
      enabled = false;
    }else if (enabled) {
        auto num1 = std::stoi(match.str(1));
        auto num2 = std::stoi(match.str(2));
        valuePart2 += num1 * num2;      
    }
  }
  return valuePart2;
}

export void solve(const std::filesystem::path &inputPath) {
  auto input = std::ifstream(inputPath);
  if (!input.is_open()) {
    std::cerr << "Failed to open " << inputPath << "\n";
    return;
  }
  auto line = std::string();
  auto valuePart1 = 0;
  auto valuePart2 = 0;
  auto data = std::vector<std::string>();
  while (std::getline(input, line)) {
    data.push_back(line);
  }

  bool enabled = true;

  for (auto line : data) {
    valuePart1 += matchStringForPartOne(line);
    valuePart2 += matchStringForPartTwo(line, enabled);
  }

  std::cout << "Answer to day 3 part 1 : " << valuePart1 << "\n";
  std::cout << "Answer to day 3 part 2 : " << valuePart2 << "\n";
}
} // namespace Day3
