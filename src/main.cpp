#include <filesystem>
#include <iostream>
#include <string>

// Import daily modules
import Day1;
import Day2;

int main(int argc, char *argv[]) {
  std::filesystem::path workingDir;
  if (argc < 2) {
    workingDir = std::filesystem::current_path() / ".." / "..";
  } else {
    workingDir = argv[1];
  }

  // Example usage of Day1 module
  Day1::solve(workingDir / "assets" / "1" / "input.txt");
  Day2::solve(workingDir / "assets" / "2" / "input.txt");

  return 0;
}
