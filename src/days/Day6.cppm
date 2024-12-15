module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

export module Day6;

namespace Day6 {

enum class State {
  Empty,
  OBSTACLE,
  GaurdHasVisited,
};
const auto testData = std::vector<std::string>{
    "....#.....", ".........#", "..........", "..#.......", ".......#..",
    "..........", ".#..^.....", "........#.", "#.........", "......#..."};

enum class Direction {
  NoGaurd,
  Up,
  Down,
  Left,
  Right,
};

using Room1518Layout = std::vector<std::vector<State>>;
using Room1518Directions = std::vector<std::vector<Direction>>;
using Position = std::tuple<int, int>;

auto RotateGaurd(auto gaurdDir) {
  switch (gaurdDir) {
  case Direction::Up:
    return Direction::Right;
  case Direction::Right:
    return Direction::Down;
  case Direction::Down:
    return Direction::Left;
  case Direction::Left:
    return Direction::Up;
  default:
    return gaurdDir;
  }
}

auto findGaurd(auto room) {
  for (auto i = 0; i < room.size(); ++i) {
    for (auto j = 0; j < room[i].size(); ++j) {
      if (room[i][j] == State::GaurdHasVisited) {
        return Position{i, j};
      }
    }
  }
  return Position{-1, -1};
}

auto MoveGaurd(Room1518Layout &room, Room1518Directions &roomWithDir,
               Position &gaurd) {
  auto [i, j] = gaurd;
  auto gaurdDir = roomWithDir[i][j];
  auto roomState = room[i][j];
  auto [di, dj] = std::tuple{0, 0};
  switch (gaurdDir) {
  case Direction::Up:
    di = -1;
    break;
  case Direction::Left:
    dj = -1;
    break;
  case Direction::Right:
    dj = 1;
    break;
  case Direction::Down:
    di = 1;
    break;
  default:
    std::cout << "Invalid gaurd state" << std::endl;
    return false;
  }
  auto newI = i + di;
  auto newJ = j + dj;
  if (newI < 0 || newI >= room.size() || newJ < 0 ||
      newJ >= room[newI].size()) {
    return false;
  }
  if (room[newI][newJ] == State::OBSTACLE) {
    roomWithDir[i][j] = RotateGaurd(gaurdDir);
    return MoveGaurd(room, roomWithDir, gaurd);
  }
  room[i][j] = State::GaurdHasVisited;
  roomWithDir[newI][newJ] = gaurdDir;
  gaurd = Position{newI, newJ};
  return true;
}

auto CountNumberOfVisited(const auto &room) {
  auto count = 0;
  for (auto line : room) {
    for (auto state : line) {
      if (state == State::GaurdHasVisited) {
        ++count;
      }
    }
  }
  return count;
}

bool CheckIfItWouldCauseLoop(const auto &roomWithDir, const auto &gaurd) {
  auto [i, j] = gaurd;
  auto [di, dj] = std::tuple{0, 0};
  switch (roomWithDir[i][j]) {
  case Direction::Up:
    di = -1;
    break;
  case Direction::Left:
    dj = -1;
    break;
  case Direction::Right:
    dj = 1;
    break;
  case Direction::Down:
    di = 1;
    break;
  default:
    std::cout << "Invalid gaurd state" << std::endl;
    return false;
  }
  if (i + di < 0 || i + di >= roomWithDir.size() || j + dj < 0 ||
      j + dj >= roomWithDir[i].size())
    return false;
  return roomWithDir[i + di][j + dj] == roomWithDir[i][j];
}

void UpdateBlocksIfBlockWouldCauseLoop(auto &blocks, const auto &room,
                                       const auto &roomWithDir, auto gaurd) {
  auto newRoom = room;
  auto newRoomWithDir = roomWithDir;
  auto [i, j] = gaurd;
  auto [newI, newJ] = gaurd;
  switch (newRoomWithDir[i][j]) {
  case Direction::Up:
    newI = i - 1;
    break;
  case Direction::Left:
    newJ = j - 1;
    break;
  case Direction::Right:
    newJ = j + 1;
    break;
  case Direction::Down:
    newI = i + 1;
    break;
  default:
    return;
  }
  if (newI < 0 || newI >= newRoom.size() || newJ < 0 ||
      newJ >= newRoom[newI].size())
    return;
  if (newRoom[newI][newJ] == State::OBSTACLE)
    return;
  newRoom[newI][newJ] = State::OBSTACLE;
  /*if (blocks.find(Position{newI, newJ}) != blocks.end())
    return;*/
  auto newGaurd = gaurd;
  std::set<std::pair<Position, Direction>> visited;
  std::set<Position> visitedPositions;
  auto counter = 0;
  while (MoveGaurd(newRoom, newRoomWithDir, newGaurd)) {
    /*
    todo Figure out the bug??
    auto [gI, gJ] = newGaurd;
    auto currentDirection = newRoomWithDir[gI][gJ];
    if (newGaurd != gaurd &&
        visited.find(std::pair<Position, Direction>(
            newGaurd, currentDirection)) != visited.end()) {
      blocks.insert(Position{newI, newJ});
      break;
    }
    visited.insert(std::pair<Position, Direction>(newGaurd,
    currentDirection));*/
    if (counter > 50000) {
      blocks.insert(Position{newI, newJ});
      break;
    }
    ++counter;
  }
}

void CheckAllPossiblities(auto &blocks, const Room1518Layout &room,
                          const Room1518Directions &roomWithDir,
                          const auto &gaurd) {

  for (auto i = 0; i < room.size(); ++i) {
    for (auto j = 0; j < room[i].size(); ++j) {
      if (room[i][j] != State::GaurdHasVisited ||
          (i == std::get<0>(gaurd) && j == std::get<1>(gaurd)))
        continue;

      auto newRoom = room;
      auto newRoomWithDir = roomWithDir;
      newRoom[i][j] = State::OBSTACLE;
      auto newGaurd = gaurd;

      std::set<std::pair<Position, Direction>> visited;
      std::set<Position> visitedPositions;
      while (MoveGaurd(newRoom, newRoomWithDir, newGaurd)) {
        auto [gI, gJ] = newGaurd;
        auto currentDirection = newRoomWithDir[gI][gJ];
        if (newGaurd != gaurd &&
            visited.find(std::pair<Position, Direction>(
                newGaurd, currentDirection)) != visited.end()) {
          blocks.insert(Position{i, j});
          break;
        }
        visited.insert(
            std::pair<Position, Direction>(newGaurd, currentDirection));
      }
    }
  }
}

export void solve(const std::filesystem::path &inputPath) {
  std::vector<std::string> lines;
  auto room = Room1518Layout();
  auto roomDir = Room1518Directions();
  auto line = std::string();

  if (false) {
    lines = testData;
  } else {
    auto input = std::ifstream(inputPath);
    if (!input.is_open()) {
      std::cerr << "Failed to open " << inputPath << "\n";
      return;
    }

    while (std::getline(input, line)) {
      lines.push_back(line);
    }
  }
  for (auto line : lines) {
    auto roomLine = std::vector<State>();
    auto roomDirLine = std::vector<Direction>();
    for (auto c : line) {
      switch (c) {
      case '#':
        roomLine.push_back(State::OBSTACLE);
        roomDirLine.push_back(Direction::NoGaurd);
        break;
      case '^':
        roomLine.push_back(State::GaurdHasVisited);
        roomDirLine.push_back(Direction::Up);
        break;
      case '.':
      default:
        roomLine.push_back(State::Empty);
        roomDirLine.push_back(Direction::NoGaurd);
        break;
      }
    }
    room.push_back(roomLine);
    roomDir.push_back(roomDirLine);
  }

  auto valuePart1 = 0;
  auto valuePart2 = 0;
  auto stepsTaken = 0;

  auto gaurd = findGaurd(room);
  auto gaurdStartPos = gaurd;
  auto possibleBlocks = std::set<Position>();
  while (MoveGaurd(room, roomDir, gaurd)) {
    ++stepsTaken;
    // UpdateBlocksIfBlockWouldCauseLoop(possibleBlocks, room, roomDir, gaurd);
  }
  valuePart1 = CountNumberOfVisited(room) + 1;
  possibleBlocks.clear();
  CheckAllPossiblities(possibleBlocks, room, roomDir, gaurdStartPos);
  valuePart2 = possibleBlocks.size() + 1;

  // Print(room);
  // PrintVisited(roomVisited);
  std::cout << "Part1: " << valuePart1 << std::endl;
  std::cout << "Part2: " << valuePart2 << std::endl;
}
} // namespace Day6