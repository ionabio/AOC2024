module;
#include <cmath>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

export module Day14;
import Files;

namespace Day14 {
struct Point {
  int x;
  int y;
};
using Velocity = Point;
using Size = Point;

struct Robot {
  Point position;
  Velocity velocity;
};

std::vector<std::string> testData = {
"p=0,4 v=3,-3",
"p=6,3 v=-1,-3",
"p=10,3 v=-1,2",
"p=2,0 v=2,-1",
"p=0,0 v=1,3",
"p=3,0 v=-2,-2",
"p=7,6 v=-1,-3",
"p=3,0 v=-1,-2",
"p=9,3 v=2,3",
"p=7,3 v=-1,2",
"p=2,4 v=2,-3",
"p=9,5 v=-3,-3",
};

auto ParseRobots(const auto &lines) -> std::vector<Robot> {
  auto robots = std::vector<Robot>{};
  for (const auto &line : lines) {
    auto PxPos = line.find("p=");
    auto PyPos = line.find(",");
    auto VxPos = line.find("v=");
    auto VyPos = line.find(",", VxPos + 1);
    auto Px = line.substr(PxPos + 2, PyPos - PxPos - 2);
    auto Py = line.substr(PyPos + 1, VxPos - PyPos - 2);
    auto Vx = line.substr(VxPos + 2, VyPos - VxPos - 2);
    auto Vy = line.substr(VyPos + 1);
    robots.push_back(
        {{std::stoi(Px), std::stoi(Py)}, {std::stoi(Vx), std::stoi(Vy)}});
  }
  return robots;
}

auto buildGrid(const auto &robots, const Size &size) -> std::vector<std::vector<int>> {
    std::vector<std::vector<int>> grid(size.y, std::vector<int>(size.x, 0));
    for (const auto &robot : robots) {
        ++grid[robot.position.y][robot.position.x];
    }
    return grid;
}

auto PrintRobots(const auto &robots, const Size &size, bool printOccupied = false) -> void {
 auto grid = buildGrid(robots, size);
  for (const auto &row : grid) {
    for (const auto &cell : row) {
      if (printOccupied) 
        std::cout << (cell > 0 ? "*" : ".");
      else
        std::cout << cell;
    }
    std::cout << std::endl;
  }
}

auto TelePort(const int pos, const int size) -> int {
  auto newPos = pos;
  if (pos < 0)
    newPos = size + pos;
  if (pos >= size)
    newPos = pos - size;
  return newPos;
}

void MoveRobotos(auto &robots, const Size &size)
{
    for(auto &robot : robots){
        robot.position.x += robot.velocity.x;
        robot.position.x = TelePort(robot.position.x, size.x);
        robot.position.y += robot.velocity.y;
        robot.position.y = TelePort(robot.position.y, size.y);
        
    }   
}

auto calculateQuadrant(const auto &robots, const Size &size)
{
    auto topLeft = 0;
    auto topRight = 0;
    auto bottomLeft = 0;
    auto bottomRight = 0;
    Size midLine = {size.x / 2, size.y / 2};
    for(const auto &robot : robots){
        if(robot.position.x < midLine.x && robot.position.y < midLine.y)
            ++topLeft;
        else if(robot.position.x < midLine.x && robot.position.y > midLine.y)
            ++bottomLeft;
        else if(robot.position.x > midLine.x && robot.position.y < midLine.y)
            ++topRight;
        else if(robot.position.x > midLine.x && robot.position.y > midLine.y)
            ++bottomRight;
    }
    return std::tuple{topLeft, topRight, bottomLeft, bottomRight};
}

auto CheckChristmassTreePossiblity(const auto &robots, const Size &size) -> bool {
    auto grid = buildGrid(robots, size);
    for(const auto &row : grid){
        for(const auto &cell : row){
            if(cell > 1)
                return false;
        }
    }
    return true;
}

export auto solve(const std::filesystem::path &input) -> void {
  Size size {101, 103};
  auto lines = Files::readFile(input);

  auto robots = ParseRobots(lines);  
  for(int i = 0; i < 100; ++i){
    MoveRobotos(robots, size);  
  }
  auto [tl, tr, bl, br] = calculateQuadrant(robots, size);
  std::cout << "Part 1: " << tl * tr * bl * br << std::endl;
  for (int i = 0; i < 100000; ++i){
    MoveRobotos(robots, size);  
    if(CheckChristmassTreePossiblity(robots, size)){
        PrintRobots(robots, size, true);
        std::cout << "Part 2: " << i+100 << std::endl;
    
    }
  }

}
} // namespace Day14
