module;
#include <filesystem>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

export module Day18;
import Files;

namespace Day18 {
struct Position {
  int x;
  int y;
  bool operator==(const Position &other) const {
    return x == other.x && y == other.y;
  }
  Position operator+(const Position &other) const {
    return {x + other.x, y + other.y};
  }
};
using Size = Position;
auto parseWalls(std::vector<std::string> lines) {
  std::vector<Position> walls;
  for (auto line : lines) {
    // split two numbers from comma
    auto comma = line.find(',');
    auto x = std::stoi(line.substr(0, comma));
    auto y = std::stoi(line.substr(comma + 1));
    walls.push_back({x, y});
  }
  return walls;
}
enum GridType { Empty, Wall };
struct State {
  Position pos;
  Position parent;
  int steps;
  bool operator<(const State &other) const { return steps > other.steps; }
};

std::vector<Position> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool isWall(int step, Position pos, std::vector<Position> walls) {
  for (int i = 0; i <= step; ++i) {
    if (walls[i] == pos) {
      return true;
    }
  }
  return false;
}

bool findPath(const Size &size, const State initialState, const Position &end,
              const std::vector<Position> &walls, int wallStep, int &steps) {
  std::vector<std::vector<bool>> visited(size.x, std::vector<bool>(size.y));

  std::priority_queue<State> statesToAnalyse;
  statesToAnalyse.push(initialState);

  bool pathFound = false;
  while (!statesToAnalyse.empty()) {
    auto state = statesToAnalyse.top();
    steps = state.steps;

    statesToAnalyse.pop();
    if (state.pos == end) {
      pathFound = true;
      break;
    }
    if (visited[state.pos.x][state.pos.y]) {
      continue;
    }
    visited[state.pos.x][state.pos.y] = true;
    for (int i = 0; i < 4; ++i) {
      auto newPos = state.pos + directions[i];
      if (newPos.x < 0 || newPos.x >= size.x || newPos.y < 0 ||
          newPos.y >= size.y) {
        continue;
      }
      if (isWall(wallStep, newPos, walls)) {
        continue;
      }
      statesToAnalyse.push({newPos, state.pos, state.steps + 1});
    }
  }
  return pathFound;
}

void TestPath(const Size &size, const State initialState, const Position &end,
              const std::vector<Position> &walls, int wallStep) {
                auto steps = 0;
  auto found = findPath(size, initialState, end, walls, wallStep, steps);
  std::cout << wallStep << " walls "
            << (found ? "path found" : "no path found ")
            << "walls: " << walls[wallStep].x << ", " << walls[wallStep].y 
            << " steps: " << steps
            << std::endl;
}
export void solve(std::filesystem::path input) {
  auto lines = Files::readFile(input);
  auto walls = parseWalls(lines);
  Size size = {71, 71};
  auto start = Position{0, 0};
  auto end = Position{size.x - 1, size.y - 1};
  auto initialState = State{start, start, 0};

  auto foundSolution = false;

  int i = 0;
  int iDelta = 500;
  TestPath(size, initialState, end, walls, 1024);
  while (iDelta > 0) {
    if (i >= walls.size()) {
      i = walls.size() - 1;
    }
    int dummy;
    if (findPath(size, initialState, end, walls, i ,dummy)) {
      i += iDelta; // Increase i by the step size
    } else {
      iDelta /= 2; // Decrease the step size
      i -= iDelta; // Adjust i to try again with a smaller step
    }
  }
  TestPath(size, initialState, end, walls, i - 2);
  TestPath(size, initialState, end, walls, i - 1);
  TestPath(size, initialState, end, walls, i);
  TestPath(size, initialState, end, walls, i + 1);
  // apparently i - 1 would be the solution.
}
} // namespace Day18