module;

#include <filesystem>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

export module Day16;

import Files;

namespace Day16 {

// clang-format off
std::vector<std::string> testData = {
"###############",
"#.......#....E#",
"#.#.###.#.###.#",
"#.....#.#...#.#",
"#.###.#####.#.#",
"#.#.#.......#.#",
"#.#.#####.###.#",
"#...........#.#",
"###.#.#####.#.#",
"#...#.....#.#.#",
"#.#.#.###.#.#.#",
"#.....#...#.#.#",
"#.###.#.#.#.#.#",
"#S..#.....#...#",
"###############"
};
// clang-format on

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

enum GridType { Empty, Start, End, Wall };

using Grid = std::vector<std::vector<GridType>>;
using Vec = Position;
using Cost = uint64_t;

enum Direction { East, South, West, North };
std::vector<Vec> dirVecs = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // we can cast directly to get positions

struct DeerState {
  Cost cost;
  Position pos;
  Direction dir;
  bool operator<(const DeerState &other) const { return cost > other.cost; }
};

using VisitedCosts = std::vector<std::vector<std::vector<Cost>>>;

auto ParseGrid(const std::vector<std::string> &lines) -> Grid {
  Grid grid;
  for (const auto &line : lines) {
    std::vector<GridType> row;
    for (const auto &c : line) {
      switch (c) {
      case '#':
        row.push_back(GridType::Wall);
        break;
      case 'S':
        row.push_back(GridType::Start);
        break;
      case 'E':
        row.push_back(GridType::End);
        break;
      case '.':
      default:
        row.push_back(GridType::Empty);
        break;
      }
    }
    grid.push_back(row);
  }
  return grid;
}

std::tuple<Position, Position> findStartEnd(const Grid &grid) {
  Position start = {-1, -1};
  Position end = {-1, -1};
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[i].size(); ++j) {
      if (grid[i][j] == GridType::Start) {
        start = {i, j};
      }
      if (grid[i][j] == GridType::End) {
        end = {i, j};
      }
    }
  }
  return {start, end};
}

export void solve(std::filesystem::path input_path) {
  auto lines = Files::readFile(input_path);
  auto grid = ParseGrid(lines);
  auto rows = grid.size();
  auto cols = grid[0].size();
  auto [start, end] = findStartEnd(grid);

  std::priority_queue<DeerState> statesToAnalyse;

  // Visited states: (x, y, direction)
  VisitedCosts visited(
      rows, std::vector<std::vector<Cost>>(
                cols, std::vector<Cost>(4, std::numeric_limits<Cost>::max())));

  DeerState initial = {0, start, East};
  statesToAnalyse.push(initial);
  visited[start.x][start.y][East] = 0;
  int lowestScore = 0;
  while (!statesToAnalyse.empty()) {
    DeerState current =
        statesToAnalyse.top(); // Always gives the lowest cost to analyse first
    statesToAnalyse.pop();

    if (current.pos == end) {
      lowestScore = current.cost;
      break;
    }

    // Move forward
    auto dir = dirVecs[static_cast<int>(current.dir)];
    auto new_pos = current.pos + dir;
    if (new_pos.x >= 0 && new_pos.x < rows && new_pos.y >= 0 &&
        new_pos.y < cols && grid[new_pos.x][new_pos.y] != GridType::Wall) {
      Cost new_cost = current.cost + 1;
      if (new_cost < visited[new_pos.x][new_pos.y][current.dir]) {
        visited[new_pos.x][new_pos.y][current.dir] = new_cost;
        statesToAnalyse.push(DeerState{new_cost, new_pos, current.dir});
      }
    }

    // Rotate clockwise
    Direction cw_dir = static_cast<Direction>((current.dir + 1) % 4);
    Cost cw_cost = current.cost + 1000;
    if (cw_cost < visited[current.pos.x][current.pos.y][cw_dir]) {
      visited[current.pos.x][current.pos.y][cw_dir] = cw_cost;
      statesToAnalyse.push(DeerState{cw_cost, current.pos, cw_dir});
    }

    // Rotate counterclockwise
    Direction ccw_dir = static_cast<Direction>((current.dir + 3) % 4);
    Cost ccw_cost = current.cost + 1000;
    if (ccw_cost < visited[current.pos.x][current.pos.y][ccw_dir]) {
      visited[current.pos.x][current.pos.y][ccw_dir] = ccw_cost;
      statesToAnalyse.push(DeerState{ccw_cost, current.pos, ccw_dir});
    }
  }

  std::cout << "Lowest score (Part 1): " << lowestScore << std::endl;
}

} // namespace Day16
