module;
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

export module Day11;
namespace Day11 {
using Stones = std::map<long long, long long>;
Stones testStones = {{125ll, 1}, {17ll, 1}};
auto readFile(const std::filesystem::path &inputPath) {
  auto file = std::ifstream(inputPath);
  auto stones = Stones();
  std::string line;
  while (std::getline(file, line)) {
    // SPLIT LINE WITH SPACES AND GET THE NUMBERS
    std::stringstream ss(line);
    std::string word;
    while (ss >> word) {
      auto stone = std::stoll(word);
      if (stones.find(stone) == stones.end()) {
        stones[stone] = 1;
      } else {
        stones[stone]++;
      }
    }
  }
  return stones;
}

auto countDigits(long long n) {
  if (n == 0)
    return 1;
  if (n < 0)
    n = -n;
  return 1 + static_cast<int>(std::log10(n));
}

auto blink(auto &stones) {
  auto newStones = Stones();
  for (auto &stone : stones) {
    if (stone.first == 0) {
      newStones[1] += stone.second;    
    } else if (countDigits(stone.first) % 2 == 0) {
      auto digits = countDigits(stone.first);
      auto left = stone.first / (long long)std::pow(10ll, digits / 2);
      auto right = stone.first - left * (long long)std::pow(10ll, digits / 2);
      newStones[left] += stone.second;
      newStones[right] += stone.second;
    } else {
      newStones[stone.first * 2024] += stone.second;
    }
  }
  return newStones;
}



export void solve(const std::filesystem::path &inputPath) {
  auto stones = readFile(inputPath);
  auto memos = std::map<long long, std::vector<long long>>();
  auto part1 = 25;
  auto part2 = 75;
  int i = 0;
  for (; i < part1; i++) {
    stones = blink(stones);
  }
  auto sumPart1 = 0ll;
  for (auto &stone : stones) {
    sumPart1 += stone.second;
  }
  std::cout << "Part 1 : " << sumPart1 << std::endl;
  for (; i < part2; i++) {
    stones = blink(stones);
  }
  auto sumPart2 = 0ll;
  for (auto &stone : stones) {
    sumPart2 += stone.second;
  }
  std::cout << "Part 2 : " << sumPart2 << std::endl;
}
} // namespace Day11