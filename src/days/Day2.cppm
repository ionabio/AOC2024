module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

export module Day2;

namespace Day2 {
auto isWithinRange(const auto distance) {
  return std::abs(distance) >= 1 && std::abs(distance) <= 3;
}
auto isSafe(const auto &numbers) {
  auto direction = numbers[1] - numbers[0]; // ascending [+] or descending [-]
  if (!isWithinRange(direction)) {
    return false;
  }
  for (auto i = 1; i < numbers.size()-1; ++i) {
    auto distance =  numbers[i + 1] - numbers[i];
    if (!isWithinRange(distance) || distance * direction < 0) {
      return false;
    }
  }
  return true;
}
auto isSafeWithDampening(const auto &numbers) { 
for (auto i = 0; i < numbers.size(); ++i) {
    auto copy = numbers;
    copy.erase(copy.begin() + i);
    if (isSafe(copy)) {
      return true;
    }
  }
  return false; 
 }

export void solve(const std::filesystem::path &inputPath) {
  auto input = std::ifstream(inputPath);
  if (!input.is_open()) {
    std::cerr << "Failed to open " << inputPath << "\n";
    return;
  }

  using Day2Data = std::vector<std::vector<int>>;
  auto data = Day2Data();
  auto line = std::string();
  while (std::getline(input, line)) {
    auto numbers = std::vector<int>();
    auto iss = std::istringstream(line);
    auto numberInString = std::string();
    while (iss >> numberInString) {
      numbers.push_back(std::stoi(numberInString));
    }
    data.push_back(numbers);
  }
  auto safes = 0;
  auto safesWithDampening = 0;
  for (auto numbers : data) {
    if (isSafe(numbers)) {
      ++safes;
      ++safesWithDampening;
    } else if (isSafeWithDampening(numbers)) {
      ++safesWithDampening;
    }
  }
  std::cout << "Day 2 solution (Part A) the number of safe sequences are: "
            << safes << "\n";
  std::cout << "Day 2 solution (Part B) the number of safe sequences with "
               "dampening are: "
            << safesWithDampening << "\n";
}
} // namespace Day2
