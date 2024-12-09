module;

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
export module Day9;

namespace Day9 {
using Data = std::vector<int>; //-1 is empty, rest ID
using ParsedFile = std::vector<std::string>;
struct Info {
  int startPos;
  int size;
};

using Files = std::map<int, Info>;
using EmptySpaces = std::vector<Info>;

ParsedFile testData = {"2333133121414131402"};

auto parseInput(std::filesystem::path input_path) -> ParsedFile {
  std::vector<std::string> lines;
  std::ifstream file(input_path);
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

auto parseData(auto parsedFile) -> Data {
  auto data = Data();
  int id = 0;
  bool isParsingData = true; // alternates between data and empty space
  for (auto line : parsedFile) {
    for (auto c : line) {
      // convert to int
      if (c == '\n')
        continue;
      int value = c - '0';
      for (int i = 0; i < value; ++i) {
        if (isParsingData)
          data.push_back(id);
        else
          data.push_back(-1);
      }
      isParsingData = !isParsingData;
      if (isParsingData)
        ++id;
    }
  }
  return data;
}

auto ParseBlocked(const auto &parsedFile) {
  auto files = Files();
  auto emptySpaces = EmptySpaces();
  int id = 0;
  bool isParsingData = true; // alternates between data and empty space
  int currentSize = 0;
  for (auto line : parsedFile) {
    for (auto c : line) {
      if (c == '\n')
        continue;
      int value = c - '0';
      if (isParsingData) {
        files[id] = {currentSize, value};
      } else {
        emptySpaces.push_back({currentSize, value});
      }
      currentSize += value;
      isParsingData = !isParsingData;
      if (isParsingData)
        ++id;
    }
  }
  return std::make_tuple(files, emptySpaces);
}

auto Defrag(const auto &olddata) -> Data {
  auto data = olddata;
  size_t left = 0;
  size_t right = data.size() - 1;

  while (left < right) {
    while (left < right && data[left] != -1) {
      ++left;
    }

    while (left < right && data[right] == -1) {
      --right;
    }

    if (left < right) {
      data[left] = data[right];
      data[right] = -1;
      ++left;
      --right;
    }
  }

  data.erase(std::remove(data.begin(), data.end(), -1), data.end());

  return data;
}

auto DefragPart2(const auto &oldFiles, const auto &oldEmptySpaces) {
  auto newFiles = oldFiles;
  auto newEmptySpaces = oldEmptySpaces;
  int i = newFiles.size() - 1;
  for (; i >= 0; --i) {
    auto &file = newFiles[i];
    auto emptySpace = std::find_if(
        newEmptySpaces.begin(), newEmptySpaces.end(),
        [&](auto &emptySpace) { return emptySpace.size >= file.size && emptySpace.startPos < file.startPos; });
    if (emptySpace != newEmptySpaces.end()) {
      file.startPos = emptySpace->startPos;
      emptySpace->size -= file.size;
      if (emptySpace->size == 0) {
        newEmptySpaces.erase(emptySpace);
      } else {
        emptySpace->startPos += file.size;
      }
    }
    // merge empty spaces
    auto emptySpaceToMerge = newEmptySpaces.begin();
    while (emptySpaceToMerge != newEmptySpaces.end() - 1) {
      auto emptySpaceToMerge2 = emptySpaceToMerge + 1;
      std::vector<EmptySpaces::iterator> toErase;
      while (emptySpaceToMerge2 != newEmptySpaces.end()) {
        if (emptySpaceToMerge->startPos + emptySpaceToMerge->size ==
            (emptySpaceToMerge2)->startPos) {
          emptySpaceToMerge->size += (emptySpaceToMerge2)->size;
          toErase.push_back(emptySpaceToMerge2);
        }
        else{
          break;
        }
        ++emptySpaceToMerge2;
      }
      for (auto &erase : toErase) {
        newEmptySpaces.erase(erase);
      }
      ++emptySpaceToMerge;
    }
  }
  return newFiles;
}

auto CalculateCheckSum(const auto &data) {
  auto sum = 0ll;
  for (int i = 0; i < data.size(); ++i) {
    if (data[i] == -1)
      continue;
    sum += (long)data[i] * (long)i;
  }
  return sum;
}

auto CalculateCheckSumPart2(auto &files) {
  auto sum = 0ll;
  for (auto i = 0; i < files.size(); ++i) {
    auto &file = files[i];
    for (auto j = 0; j < file.size; ++j) {
      sum += i * ((long)file.startPos + j);
    }
  }
  return sum;
}

export void solve(std::filesystem::path input_path) {
  auto parsedFile = parseInput(input_path);
  auto data = parseData(parsedFile);
  auto newData = Defrag(data);
  auto [files, emptySpaces] = ParseBlocked(parsedFile);
  auto newFiles = DefragPart2(files, emptySpaces);
  std::cout << std::to_string(CalculateCheckSum(newData)) << "\n";
  std::cout << std::to_string(CalculateCheckSumPart2(newFiles)) << "\n";
}

} // namespace Day9