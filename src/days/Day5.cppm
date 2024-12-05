module;
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <utility>

export module Day5;

namespace Day5 {

auto parseRule(const auto &line) {
  size_t delimiterPos = line.find('|');
  if (delimiterPos == std::string::npos) {
    throw std::invalid_argument("Delimiter '|' not found in rule line.");
  }

  int part1 = std::stoi(line.substr(0, delimiterPos));
  int part2 = std::stoi(line.substr(delimiterPos + 1));
  return std::make_tuple(part1, part2);
}

// Function to parse a CSV line into integers
auto parseCSVLine(const auto &line) {
  std::vector<int> numbers;
  std::stringstream ss(line);
  std::string token;

  while (std::getline(ss, token, ',')) {
    try {
      numbers.emplace_back(std::stoi(token));
    } catch (const std::invalid_argument &) {
      std::cerr << "Warning: Skipping invalid integer '" << token
                << "' in CSV line.\n";
    }
  }

  return numbers;
}

bool checkRule(const auto &book, const auto &rule) {
  auto first = std::find(book.begin(), book.end(), std::get<0>(rule));
  auto second = std::find(book.begin(), book.end(), std::get<1>(rule));
  if (first == book.end() || second == book.end()) // the rule doesn't apply
  {
    return true;
  }
  return std::distance(book.begin(), first) <
         std::distance(book.begin(), second);
}

auto checkAndReturnBook(const auto &book, const auto &rules) {
  for (const auto &rule : rules) {
    if (!checkRule(book, rule)) {
      return 0;
    }
  }
  // return middle of the book
  return book[book.size() / 2];
}

auto reOrderBook(auto &book, auto &rules) {
    std::vector<int> tempBook = book;
    for (auto i = tempBook.size() - 1; i > 0; i--) {
        for (auto j = tempBook.size() - 1; j >= tempBook.size() - i; j--) {
            int x = tempBook[j - 1];
            int y = tempBook[j];
            for (const auto &rule : rules) {
                if (x == std::get<1>(rule) && y == std::get<0>(rule)) {
                    std::swap(tempBook[j - 1], tempBook[j]);
                    break;
                }
            }
        }
    }
    return tempBook;
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
  auto rules = std::vector<std::tuple<int, int>>();
  auto books = std::vector<std::vector<int>>();
  while (std::getline(input, line)) {
    if (line.find('|') != std::string::npos) {
      // Line contains a rule
      rules.emplace_back(parseRule(line));
    } else if (line.find(',') != std::string::npos) {
      // Line contains CSV integers
      std::vector<int> parsedNumbers = parseCSVLine(line);
      books.push_back(parsedNumbers);
    }
  }
  for (const auto &book : books) {
    auto middlePage = checkAndReturnBook(book, rules);
    if (middlePage != 0) {
      valuePart1 += middlePage;
    }
    else{
        auto reorderedBook = reOrderBook(book, rules);
        middlePage = reorderedBook[reorderedBook.size() / 2];
        valuePart2 += middlePage;
    }
  }
  std::cout << "Part 1: " << valuePart1 << std::endl;
  std::cout << "Part 2: " << valuePart2 << std::endl;
}
} // namespace Day5
