module;
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
export module Day13;

import Files;

namespace Day13 {

std::vector<std::string> testData = {
    "Button A: X+94, Y+34",    "Button B: X+22, Y+67",
    "Prize: X=8400, Y=5400",   "",
    "Button A: X+26, Y+66",    "Button B: X+67, Y+21",
    "Prize: X=12748, Y=12176", "",
    "Button A: X+17, Y+86",    "Button B: X+84, Y+37",
    "Prize: X=7870, Y=6450",   "",
    "Button A: X+69, Y+23",    "Button B: X+27, Y+71",
    "Prize: X=18641, Y=10279", "",
};
struct Config {
  double x;
  double y;

  bool operator==(const Config &other) const {
    return x == other.x && y == other.y;
  }
};

using PrizeLocation = Config;

struct Machine {
  Config A;
  Config B;
  PrizeLocation prize;
};

auto parseMachines(const std::vector<std::string> &lines)
    -> std::vector<Machine> {
  // strings in format:
  // Button A: X+26, Y+64
  // Button B: X+72, Y+48
  // Prize: X=5834, Y=8416
  std::vector<Machine> machines;
  int j = 0;
  while (j < lines.size()) {
    Machine machine;
    for (int i = 0; i < 4; i++) {
      auto currentLine = lines[j++];
      if (currentLine.empty())
        continue;
      auto x =
          currentLine.substr(currentLine.find("X") + 2,
                             currentLine.find(",") - currentLine.find("X") - 2);
      auto y = currentLine.substr(currentLine.find("Y") + 2);

      if (currentLine.find("Button A:") != std::string::npos) {
        machine.A.x = std::stoi(x);
        machine.A.y = std::stoi(y);
      }
      if (currentLine.find("Button B:") != std::string::npos) {
        machine.B.x = std::stoi(x);
        machine.B.y = std::stoi(y);
      }
      if (currentLine.find("Prize:") != std::string::npos) {
        machine.prize.x = std::stoi(x);
        machine.prize.y = std::stoi(y);
      }
    }
    machines.push_back(machine);
  }
  return machines;
}

auto costForMachine(const Machine &machine) -> double {
  auto scoreA = 3;
  auto scoreB = 1;

  // solve a linear equation
  //  A.x A  + B.x B = prize.x
  //  A.y A  + B.y B = prize.y

  auto det = machine.A.x * machine.B.y - machine.A.y * machine.B.x;
  if (det == 0) {
    return 0;
  }

  auto detA = machine.prize.x * machine.B.y - machine.prize.y * machine.B.x;
  auto detB = machine.A.x * machine.prize.y - machine.A.y * machine.prize.x;
  auto threshold = 1e-3;

  auto A = detA / det;
  auto B = detB / det;
  if (A < 0 || B < 0)
    return 0;
  if ((A - std::floor(A)) > threshold || (B - std::floor(B)) > threshold)
    return 0;
  return scoreA * A + scoreB * B;
}

auto correctMachine(const Machine &machine) -> Machine {
    Machine newMachine;
    const long long distance = 10000000000000;
    newMachine.A = machine.A;
    newMachine.B = machine.B;
    newMachine.prize = {machine.prize.x + distance, machine.prize.y + distance};
    return newMachine;
}

export void solve(const std::filesystem::path &inputPath) {
  auto lines = Files::readFile(inputPath);
  auto machines = parseMachines(lines);
  auto part1 = 0;
  for (const auto &machine : machines) {
    part1 += costForMachine(machine);
  }
  std::cout << "Part 1: " << part1 << std::endl;
  auto part2 = 0.0;
  for (const auto &machine : machines) {
    part2 += costForMachine(correctMachine(machine));
  }
  std::cout << "Part 2: " << (long long)part2 << std::endl;
}
} // namespace Day13
