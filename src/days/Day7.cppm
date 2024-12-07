module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


export module Day7;
namespace Day7 {
struct Data {
  long long result;
  std::vector<long long> numbers;
};

const auto testData = std::vector<std::string>{
    "190: 10 19",   "3267: 81 40 27",   "83: 17 5",
    "156: 15 6",    "7290: 6 8 6 15",   "161011: 16 10 13",
    "192: 17 8 14", "21037: 9 7 18 13", "292: 11 6 16 20"};

auto ReadFile(const auto &input_path) {
  std::vector<std::string> lines;
  std::ifstream file(input_path);
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

auto ParseLines(const std::vector<std::string> &lines) -> std::vector<Data> {
  std::vector<Data> parsedData;
  for (const auto &line : lines) {
    Data data;

    // Find the position of ": " delimiter
    size_t delimiterPos = line.find(": ");
    if (delimiterPos == std::string::npos) {
      continue;
    }

    std::string resultStr = line.substr(0, delimiterPos);
    data.result = std::stoll(resultStr);

    std::string numbersStr = line.substr(delimiterPos + 2);
    std::istringstream numbersStream(numbersStr);
    std::string number;
    while (numbersStream >> number) {
      data.numbers.push_back(std::stoll(number));
    }
    parsedData.push_back(data);
  }
  return parsedData;
}

auto CheckPart1(const auto &expected, const auto &numbers, const auto index) {
  if (index == 0) {
    return expected == numbers[0];
  }
  return ((expected % numbers[index] == 0) &&
          CheckPart1(expected / numbers[index], numbers, index - 1)) ||
         CheckPart1(expected - numbers[index], numbers, index - 1);
}

auto Contains(auto expected, auto number) {
  std::string expectedStr = std::to_string(expected);
  std::string numberStr = std::to_string(number);
  if (expectedStr == numberStr) {
    return false;
  }
  // check if expectedStr ends with numberStr
  return expectedStr.ends_with(numberStr);
}

auto Remove(auto expected, auto number) {
  std::string expectedStr = std::to_string(expected);
  std::string numberStr = std::to_string(number);
  auto result =
      std::stoll(expectedStr.substr(0, expectedStr.size() - numberStr.size()));
  return result;
}


auto CheckPart2(const auto &expected, const auto &numbers, const auto index) {
  if (index == 0) {
    return expected == numbers[0];
  }
  if (expected < numbers[index]) {
    return false;
  }

  auto newIndex = index - 1;
  return (Contains(expected, numbers[index]) &&
          CheckPart2(Remove(expected, numbers[index]), numbers, newIndex)) ||
         ((expected % numbers[index] == 0) &&
          CheckPart2(expected / numbers[index], numbers, newIndex)) ||
         CheckPart2(expected - numbers[index], numbers, newIndex);
}

export void solve(std::filesystem::path input_path) {
  std::vector<Data> numbers;
  auto lines = ReadFile(input_path);
  auto data = ParseLines(lines);
  auto resultPart1 = 0ll;
  auto resultPart2 = 0ll;
  for (auto d : data) {
    if(CheckPart1(d.result, d.numbers, d.numbers.size() - 1))
     resultPart1+= d.result;
    if(CheckPart2(d.result, d.numbers, d.numbers.size() - 1))
    resultPart2 += d.result;

  }
  std::cout << resultPart1 << "\n";
  std::cout << resultPart2 << "\n";
}
} // namespace Day7
