module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
export module Day10;
namespace Day10 {
using Data = std::vector<std::vector<int>>;
struct Point {
  int x, y;
  bool operator<(const Point &other) const {
    return x < other.x || (x == other.x && y < other.y);
  }
};
using Paths = std::vector<std::pair<Point, Point>>; // for zero to nine
using UniquePaths = std::set<std::pair<Point, Point>>;

auto readFile(const std::filesystem::path &inputPath) {
  std::ifstream file(inputPath);
  Data data;
  std::string line;
  while (std::getline(file, line)) {
    std::vector<int> lineData;
    for (auto &c : line) {
      lineData.push_back(c - '0');
    }
    data.push_back(lineData);
  }
  return data;
}
auto FindSteppableNeighbors(const Data &data, const Point &p) {
  std::vector<Point> neighbors;
  if (p.y + 1 < data[0].size() && data[p.x][p.y + 1] - data[p.x][p.y] == 1) {
    neighbors.push_back({p.x, p.y + 1});
  }
  if (p.y - 1 >= 0 && data[p.x][p.y - 1] - data[p.x][p.y] == 1) {
    neighbors.push_back({p.x, p.y - 1});
  }
  if (p.x + 1 < data.size() && data[p.x + 1][p.y] - data[p.x][p.y] == 1) {
    neighbors.push_back({p.x + 1, p.y});
  }
  if (p.x - 1 >= 0 && data[p.x - 1][p.y] - data[p.x][p.y] == 1) {
    neighbors.push_back({p.x - 1, p.y});
  }
  return neighbors;
}
void TakeStep(const Data &data, const Point &p, Paths &paths,
              const Point &origin) {
  auto neighbors = FindSteppableNeighbors(data, p);
  for (auto &n : neighbors) {
    if (data[n.x][n.y] == 9) {
      paths.push_back({origin, n});
      continue;
    }
    TakeStep(data, n, paths, origin);      
  }
}

export void solve(const std::filesystem::path &inputPath) {
  auto data = readFile(inputPath);
  auto paths = Paths();
  for (int i = 0; i < data.size(); ++i) {
    for (int j = 0; j < data[i].size(); ++j) {
      if (data[i][j] == 0) {
        Point p{i, j};
        TakeStep(data, p, paths, p);
      }
    }
  }
  auto uniquePaths = UniquePaths();
  for (auto &p : paths) {
    uniquePaths.insert(p);
  }

  std::cout << "Part 1 : " <<uniquePaths.size()	 << std::endl;
  std::cout << "Part 2 : " <<paths.size()	 << std::endl;
}
} // namespace Day10
