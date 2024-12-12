module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

export module Day12;

using Map = std::vector<std::vector<char>>;
struct Point {
  int x;
  int y;
};
using Size = Point; 
struct Region {
  char label;
  std::vector<Point> points;
  int perimeter;
  int sides;
  bool Has(Point point, const Map& map) const{
    if(point.x < 0 || point.x >= map.size() || point.y < 0 || point.y >= map[0].size()) return false;
    return std::ranges::find_if(points, [point](const Point& p) { return p.x == point.x && p.y == point.y; }) != points.end();
  }
};
using Regions = std::vector<Region>;

std::vector<Point> vertex = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}};

namespace Day12 {
auto testData = std::vector<std::string>{
    "RRRRIICCFF", "RRRRIICCCF", "VVRRRCCFFF", "VVRCCCJFFF", "VVVVCJJCFE",
    "VVIVCCJJEE", "VVIIICJJEE", "MIIIIIJJEE", "MIIISIJEEE", "MMMISSJEEE",
};

auto readFile(const std::filesystem::path &inputPath) {
  auto readData = std::vector<std::string>();
  auto file = std::ifstream(inputPath);
  std::string line;
  while (std::getline(file, line)) {
    readData.push_back(line);
  }
  return readData;
}

auto parseData(const auto &data) {
  auto map = Map();
  for (const auto &line : data) {
    map.push_back(std::vector<char>(line.begin(), line.end()));
  }
  return map;
}

auto isValidPoint(const Point& p, const Size& mapSize) -> bool {
    return p.x >= 0 && p.y >= 0 && p.x < mapSize.x && p.y < mapSize.y;
}

auto fillRegion(Map& map, Region& region, const Point& currentPoint, const Size& mapSize) -> void {
    // If point is invalid or doesn't match region label or already visited (marked as '.')
    if (!isValidPoint(currentPoint, mapSize) || 
        map[currentPoint.y][currentPoint.x] != region.label || 
        map[currentPoint.y][currentPoint.x] == '.') {
        return;
    }

    // Add point to region
    region.points.push_back(currentPoint);
    
    // Mark as visited
    map[currentPoint.y][currentPoint.x] = '.';

    // Recursively fill in all four directions
    fillRegion(map, region, {currentPoint.x + 1, currentPoint.y}, mapSize);
    fillRegion(map, region, {currentPoint.x - 1, currentPoint.y}, mapSize);
    fillRegion(map, region, {currentPoint.x, currentPoint.y + 1}, mapSize);
    fillRegion(map, region, {currentPoint.x, currentPoint.y - 1}, mapSize);
}

auto findAllRegions(const Map& originalMap) -> Regions {
    auto regions = Regions{};
    auto mapSize = Size{static_cast<int>(originalMap[0].size()), 
                       static_cast<int>(originalMap.size())};
    
    // Create a working copy of the map
    auto workingMap = originalMap;
    // Iterate through each point in the map
    for (int y = 0; y < mapSize.y; ++y) {
        for (int x = 0; x < mapSize.x; ++x) {
            if (workingMap[y][x] != '.') {  // If not already visited
                auto region = Region{};
                region.label = workingMap[y][x];
                fillRegion(workingMap, region, {x, y}, mapSize);                
                if (!region.points.empty()) {
                    regions.push_back(region);
                }
            }
        }
    }
    
    return regions;
}


auto calculatePerimeter(const Region &region, const Map &map) -> int {
  auto perimeter = 0;
  for (const auto &point : region.points) {
    // number of non equal neighbours
    auto neighbours = 0;
    if(point.x > 0 && map[point.y][point.x - 1] != region.label) neighbours++;
    if(point.x < map.size() - 1 && map[point.y][point.x + 1] != region.label) neighbours++;
    if(point.y > 0 && map[point.y - 1][point.x] != region.label) neighbours++;
    if(point.y < map[0].size() - 1 && map[point.y + 1][point.x] != region.label) neighbours++;
    if(point.x == 0) neighbours++;
    if(point.x == map.size() - 1) neighbours++;
    if(point.y == 0) neighbours++;
    if(point.y == map[0].size() - 1) neighbours++;
    perimeter += neighbours;
  }
  return perimeter;
}

auto calculateSides(const Region &region, const Map &map) -> int {
  // number of convex corners
  auto corners = 0;
  for (const auto &point : region.points) {
    for (const auto &corner : vertex) {     
      // vertices for each element is considered, and only in 3 cases they can be corners 
      // adj1| dia 
      // - - | - -
      //  x  | adj2
      //  
      // note note to confuse if adj2 could be a corner, then adj1 would act as dia, 
      // we don't consider them here, X will cover them when checking for them

      Point adj1 = {point.x + corner.x, point.y};
      Point adj2 = {point.x, point.y + corner.y};
      Point dia = {point.x + corner.x, point.y + corner.y};
      bool hasAdj1 = region.Has(adj1, map);
      bool hasAdj2 = region.Has(adj2, map);
      bool hasDia = region.Has(dia, map);
      if(hasAdj1 && hasAdj2 && !hasDia) corners++;
      else if(!hasAdj1 && !hasAdj2 && !hasDia) corners++;
      else if(!hasAdj1 && !hasAdj2 && hasDia) corners++;
    }
  }
  return corners;
}

export void solve(const std::filesystem::path &inputPath) {
    auto data = readFile(inputPath);
    auto map = parseData(data);
    
    // Find all regions
    auto regions = findAllRegions(map);
    for(auto &region : regions){
        region.perimeter = calculatePerimeter(region, map);
        region.sides = calculateSides(region, map);
    }
    // part 1
    auto part1 = 0;
    for (auto &region : regions){
        part1 += region.perimeter*region.points.size();

    }
    // part 2
    auto part2 = 0;
    for (auto &region : regions){
        part2 += region.sides*region.points.size();
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
} 
}