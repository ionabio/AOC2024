module;
#include <deque>
#include <filesystem>
#include <iostream>
#include <vector>
export module Day15;
import Files;

namespace Day15 {
std::vector<std::string> testDat = {
    "##########",
    "#..O..O.O#",
    "#......O.#",
    "#.OO..O.O#",
    "#..O@..O.#",
    "#O#..O...#",
    "#O..O..O.#",
    "#.OO.O.OO#",
    "#....O...#",
    "##########",
    "",
    "<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^",
    "vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v",
    "><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<",
    "<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^",
    "^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><",
    "^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^",
    ">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^",
    "<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>",
    "^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>",
    "v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^"};

std::vector<std::string> simpleTestData = {
    "########", "#..O.O.#", "##@.O..#", "#...O..#", "#.#.O..#",
    "#...O..#", "#......#", "########", "",         "<^^>>>vv<v>>v<<"};

enum class Direction { UP, DOWN, LEFT, RIGHT };

enum class Tile { Empty, Wall, Good, Robot };

auto toDirection(char c) -> Direction {
  switch (c) {
  case 'v':
    return Direction::DOWN;
  case '^':
    return Direction::UP;
  case '<':
    return Direction::LEFT;
  case '>':
  default:
    return Direction::RIGHT;
  }
}

auto toString(Direction direction) -> std::string {
  switch (direction) {
  case Direction::UP:
    return "^";
  case Direction::DOWN:
    return "v";
  case Direction::LEFT:
    return "<";
  case Direction::RIGHT:
  default:
    return ">";
  }
}

auto isDirection(char c) -> bool {
  return c == 'v' || c == '^' || c == '<' || c == '>';
}

auto isWall(char c) -> bool { return c == '#'; }

auto toTile(char c) -> Tile {
  switch (c) {
  case '.':
    return Tile::Empty;
  case '#':
    return Tile::Wall;
  case 'O':
    return Tile::Good;
  case '@':
  default:
    return Tile::Robot;
  }
}

auto toString(Tile tile) -> std::string {
  switch (tile) {
  case Tile::Empty:
    return ".";
  case Tile::Wall:
    return "#";
  case Tile::Good:
    return "O";
  case Tile::Robot:
  default:
    return "@";
  }
}

enum class DTile { Empty, Wall, GoodLeft, GoodRight, Robot };

auto toDTile(char tile) -> DTile {
  switch (tile) {
  case '.':
    return DTile::Empty;
  case '#':
    return DTile::Wall;
  case '[':
    return DTile::GoodLeft;
  case ']':
    return DTile::GoodRight;
  case '@':
  default:
    return DTile::Robot;
  }
}

auto toString(DTile tile) -> std::string {
  switch (tile) {
  case DTile::Empty:
    return ".";
  case DTile::Robot:
    return "@";
  case DTile::Wall:
    return "#";
  case DTile::GoodLeft:
    return "[";
  case DTile::GoodRight:
  default:
    return "]";
  }
}

using Directions = std::vector<Direction>;
using Map = std::vector<std::vector<Tile>>;
using DMap = std::vector<std::vector<DTile>>;

void ParseLines(const std::vector<std::string> &lines, Map &map,
                Directions &directions) {
  for (const auto &line : lines) {
    if (line.empty())
      continue;
    if (isDirection(line[0])) {
      for (auto c : line) {
        if (isDirection(c)) {
          directions.push_back(toDirection(c));
        }
      }
      continue;
    } else {
      std::vector<Tile> row;
      for (const auto &c : line) {
        row.push_back(toTile(c));
      }
      map.push_back(row);
    }
  }
}

struct Position {
  int x;
  int y;
  auto operator+(const Position &other) const -> Position {
    return {x + other.x, y + other.y};
  }
};

auto findRobot(const Map &map) -> Position {
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].size(); ++x) {
      if (map[y][x] == Tile::Robot) {
        return {x, y};
      }
    }
  }
  return {-1, -1};
}

auto findRobot(const DMap &map) -> Position {
  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].size(); ++x) {
      if (map[y][x] == DTile::Robot) {
        return {x, y};
      }
    }
  }
  return {-1, -1};
}

auto getMapAt(const Map &map, const Position &position) -> const Tile {
  return map[position.y][position.x];
}

void setMapAt(Map &map, const Position &position, const Tile &tile) {
  map[position.y][position.x] = tile;
}

auto findGoods(const Map &map, const Position &robot,
               const Position &scanDelta) -> std::vector<Position> {
  auto goods = std::vector<Position>();
  auto currentGood = robot + scanDelta;
  while (getMapAt(map, currentGood) == Tile::Good) {
    goods.push_back(currentGood);
    currentGood = currentGood + scanDelta;
  }
  return goods;
}

auto getScanDelta(Direction direction) -> const Position {
  switch (direction) {
  case Direction::UP:
    return {0, -1};
  case Direction::DOWN:
    return {0, 1};
  case Direction::LEFT:
    return {-1, 0};
  case Direction::RIGHT:
    return {1, 0};
  }
}

void PrintMap(const Map &map) {
  for (const auto &row : map) {
    for (const auto &tile : row) {
      std::cout << toString(tile);
    }
    std::cout << std::endl;
  }
}

bool move(Map &map, Direction direction) {
  auto robot = findRobot(map);
  auto scanDelta = getScanDelta(direction);
  auto GoodPositions = findGoods(map, robot, scanDelta);
  if (!GoodPositions.empty()) {
    auto lastGoodPosition = GoodPositions.back();
    if (getMapAt(map, lastGoodPosition + scanDelta) == Tile::Wall) {
      return false;
    }
    for (auto goodPosition : GoodPositions) {
      setMapAt(map, goodPosition + scanDelta, Tile::Good);
    }
    setMapAt(map, robot, Tile::Empty);
    setMapAt(map, robot + scanDelta, Tile::Robot);
    return true;
  }
  // check wall at robot position
  if (getMapAt(map, robot + scanDelta) == Tile::Wall) {
    return false;
  }
  setMapAt(map, robot, Tile::Empty);
  setMapAt(map, robot + scanDelta, Tile::Robot);
  return true;
}

auto execute(const Map &map, const Directions &directions) -> Map {
  Map newMap = map;

  for (const auto &direction : directions) {
    move(newMap, direction); // use bool if needed in Part 2 :)
    // std::cout << "Moved " << toString(direction) << std::endl;
    //  PrintMap(newMap);
  }
  return newMap;
}

auto getGPS(const Map &map) -> int {
  auto gps = 0;
  auto mapSize = Position(map[0].size(), map.size());
  for (int y = 0; y < mapSize.y; ++y) {
    for (int x = 0; x < mapSize.x; ++x) {
      if (getMapAt(map, {x, y}) == Tile::Good) {
        gps += y * 100 + x;
      }
    }
  }
  return gps;
}

auto toDTile(Tile tile) -> std::tuple<DTile, DTile> {
  switch (tile) {
  case Tile::Empty:
    return {DTile::Empty, DTile::Empty};
  case Tile::Wall:
    return {DTile::Wall, DTile::Wall};
  case Tile::Good:
    return {DTile::GoodLeft, DTile::GoodRight};
  case Tile::Robot:
    return {DTile::Robot, DTile::Empty};
  }
}

auto generateDoubleMap(const Map &map) -> DMap {
  DMap doubleMap;
  for (const auto &row : map) {
    std::vector<DTile> doubleRow;
    for (const auto &tile : row) {
      auto [left, right] = toDTile(tile);
      doubleRow.push_back(left);
      doubleRow.push_back(right);
    }
    doubleMap.push_back(doubleRow);
  }
  return doubleMap;
}

void PrintDMap(const DMap &map) {
  for (const auto &row : map) {
    for (const auto &tile : row) {
      std::cout << toString(tile);
    }
    std::cout << std::endl;
  }
}

auto getDMapAt(const DMap &map, const Position &position) -> const DTile {
  return map[position.y][position.x];
}

auto setDMapAt(DMap &map, const Position &position, const DTile &tile) -> void {
  map[position.y][position.x] = tile;
}

auto hasWall(const DMap &map, const Position &position,
             Direction direction) -> bool {
  if (getDMapAt(map, position) != DTile::GoodLeft)
    std::cout << "Wrong call" << std::endl;
  auto scanDelta = getScanDelta(direction);
  return getDMapAt(map, position + scanDelta) == DTile::Wall ||
         getDMapAt(map, position + Position{1, 0} + scanDelta) == DTile::Wall;
}

std::vector<Position> findDGoods(const DMap &map, const Position &robot,
                                 const Position &scanDelta) {
  auto goods = std::vector<Position>();
  auto goodsToBeChecked = std::deque<Position>();
  auto currentGood = robot + scanDelta;
  auto currentGoodType = getDMapAt(map, currentGood);
  if (currentGoodType != DTile::GoodLeft && currentGoodType != DTile::GoodRight)
    return goods;
  if (currentGoodType == DTile::GoodLeft)
    goodsToBeChecked.push_back(currentGood);
  if (currentGoodType == DTile::GoodRight)
    goodsToBeChecked.push_back(currentGood + Position{-1, 0});

  while (!goodsToBeChecked.empty()) {
    auto currentGood = goodsToBeChecked.front();
    goods.push_back(currentGood);
    goodsToBeChecked.pop_front();
    if (scanDelta.x == 0) {
      // up or down, then for sure both cells need to be checked
      auto left = currentGood + scanDelta;
      auto right = currentGood + Position{1, 0} + scanDelta;
      if (getDMapAt(map, left) == DTile::GoodLeft)
        goodsToBeChecked.push_back(left);
      if (getDMapAt(map, right) == DTile::GoodLeft)
        goodsToBeChecked.push_back(right);
      if (getDMapAt(map, left) == DTile::GoodRight)
        goodsToBeChecked.push_back(left + Position{-1, 0});
    } else {
      if (getDMapAt(map, currentGood + scanDelta + scanDelta) ==
          DTile::GoodLeft)
        goodsToBeChecked.push_back(currentGood + scanDelta + scanDelta);
    }
  }

  return goods;
}

void moveGood(DMap &map, const Position &position, const Position &scanDelta) {
  // up or down movement, both places reset to empty
  if (scanDelta.x == 0) {
    setDMapAt(map, position + scanDelta, DTile::GoodLeft);
    setDMapAt(map, position + Position{1, 0} + scanDelta, DTile::GoodRight);
    setDMapAt(map, position, DTile::Empty);
    setDMapAt(map, position + Position{1, 0}, DTile::Empty);
  } else {
    if (scanDelta.x == 1) {
      // to right
      setDMapAt(map, position + scanDelta, DTile::GoodLeft);
      setDMapAt(map, position + Position{1, 0} + scanDelta, DTile::GoodRight);
      setDMapAt(map, position, DTile::Empty);
    } else {
      // to left
      setDMapAt(map, position + scanDelta, DTile::GoodLeft);
      setDMapAt(map, position + Position{1, 0}, DTile::Empty);
      setDMapAt(map, position, DTile::GoodRight);
    }
  }
}

bool move(DMap &map, Direction direction) {
  auto robot = findRobot(map);
  auto scanDelta = getScanDelta(direction);
  auto goodPositions = findDGoods(map, robot, scanDelta);
  if (!goodPositions.empty()) {
    for (auto goods : goodPositions) {
      if (hasWall(map, goods, direction)) {
        return false;
      }
    }
    if(goodPositions.size() > 1)
      int xtoBreak = 0;
    for (int j = goodPositions.size() - 1; j >= 0; --j ) {
      moveGood(map, goodPositions[j], scanDelta);      
    }
    setDMapAt(map, robot, DTile::Empty);
    setDMapAt(map, robot + scanDelta, DTile::Robot);
    return true;
  }

  if (getDMapAt(map, robot + scanDelta) == DTile::Wall) {
    return false;
  }
  setDMapAt(map, robot, DTile::Empty);
  setDMapAt(map, robot + scanDelta, DTile::Robot);
  return true;
}

auto executeDoubleMap(const DMap &map, const Directions &directions) -> DMap {
  DMap newMap = map;
  for (const auto &direction : directions) {
    //std::cout << "Moving " << toString(direction) << std::endl;
    move(newMap, direction);
   // PrintDMap(newMap);
  }
  return newMap;
}
auto getGPS(const DMap &map) -> int {
  auto gps = 0;
  auto mapSize = Position(map[0].size(), map.size());
  for (int y = 0; y < mapSize.y; ++y) {
    for (int x = 0; x < mapSize.x; ++x) {
      if (getDMapAt(map, {x, y}) == DTile::GoodLeft) {
        gps += y * 100 + x;
      }
    }
  }
  return gps;
}
export void solve(std::filesystem::path input_path) {
  auto lines = Files::readFile(input_path);
  Map map;
  Directions directions;
  ParseLines(lines, map, directions);
  PrintMap(map);
  auto newMap = execute(map, directions);
  auto gps = getGPS(newMap);
  std::cout << "Day 15" << std::endl;
  std::cout << "GPS: " << gps << std::endl;
  auto doubleMap = generateDoubleMap(map);
  PrintDMap(doubleMap);
  auto newDoubleMap = executeDoubleMap(doubleMap, directions);
  PrintDMap(newDoubleMap);
  auto gps2 = getGPS(newDoubleMap);
  std::cout << "GPS2: " << gps2 << std::endl;
}
} // namespace Day15
