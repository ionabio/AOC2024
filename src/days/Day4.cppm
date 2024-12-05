module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

export module Day4;
namespace Day4 {
const std::string xmas = "XMAS";
auto checkXMASLinearly(const auto &data, auto i, auto j) {
  auto sum = 0;
  // horizontal forward
  auto foundHF = 0, foundHB = 0;
  auto foundVF = 0, foundVB = 0;
  for (auto k = 0; k < xmas.size(); ++k) {
    if ((j + k < data[i].size()) && (data.at(i)[j + k] == xmas[k]))
      ++foundHF;
    if ((j - k >= 0) && (data.at(i)[j - k] == xmas[k]))
      ++foundHB;
    if ((i + k < data.size()) && (data.at(i + k)[j] == xmas[k]))
      ++foundVF;
    if ((i - k >= 0) && (data.at(i - k)[j] == xmas[k]))
      ++foundVB;
  }
  if (foundHF == xmas.size())
    ++sum;
  if (foundHB == xmas.size())
    ++sum;
  if (foundVF == xmas.size())
    ++sum;
  if (foundVB == xmas.size())
    ++sum;
  return sum;
}

auto checkXMASDiagonally(const auto &data, auto i, auto j) {
  auto sum = 0;
  // diagonal forward
  auto foundSE = 0, foundNW = 0;
  auto foundNE = 0, foundSW = 0;
  for (auto k = 0; k < xmas.size(); ++k) {
    if ((i + k < data.size()) && (j + k < data[i].size()) &&
        (data.at(i + k)[j + k] == xmas[k]))
      ++foundSE;
    if ((i - k >= 0) && (j - k >= 0) && (data.at(i - k)[j - k] == xmas[k]))
      ++foundNW;
    if ((i - k >= 0) && (j + k < data[i].size()) &&
        (data.at(i - k)[j + k] == xmas[k]))
      ++foundNE;
    if ((i + k < data.size()) && (j - k >= 0) &&
        (data.at(i + k)[j - k] == xmas[k]))
      ++foundSW;
  }
  if (foundSE == xmas.size())
    ++sum;
  if (foundNW == xmas.size())
    ++sum;
  if (foundNE == xmas.size())
    ++sum;
  if (foundSW == xmas.size())
    ++sum;
  return sum;
}

auto checkCrossMass(const auto &data, auto i, auto j) {
  if (i == 0 || j == 0 || i == data.size() - 1 || j == data[i].size() - 1)
    return false;
  std::vector<char> checks = {data[i - 1][j - 1], data[i - 1][j + 1],
                              data[i + 1][j - 1], data[i + 1][j + 1]};
  auto Ms = 0, Ss = 0;
  for (auto c : checks) {
    if (c == 'M')
      ++Ms;
    if (c == 'S')
      ++Ss;
  }
  if (Ms != 2 || Ss != 2)
    return false;
  if (checks[0] == 'M' && checks[3] == 'M')
    return false;
  if (checks[1] == 'M' && checks[2] == 'M')
    return false;
  return true;
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
  for (auto i = 0; i < data.size(); ++i) {
    for (auto j = 0; j < data[i].size(); ++j) {
      if (data.at(i)[j] == xmas[0]) {
        valuePart1 += checkXMASLinearly(data, i, j);
        valuePart1 += checkXMASDiagonally(data, i, j);
      }
      if (data.at(i)[j] == 'A') {
        if(checkCrossMass(data, i, j)) ++valuePart2;
      }
    }
  }
  std::cout << "Part 1: " << valuePart1 << std::endl;
  std::cout << "Part 2: " << valuePart2 << std::endl;
}

} // namespace Day4