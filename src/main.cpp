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

  //choose a day to solve
  while(true){
    std::cout << "Choose a day to solve (1-2), 0 to quit : ";
    int day;
    std::cin >> day;
    if(day == 1){
      Day1::solve(workingDir / "assets" / "1" / "input.txt");
      break;
    }else if(day == 2){
      Day2::solve(workingDir / "assets" / "2" / "input.txt");
      break;
    }else if (day == 0){
      break;
    }
    else{
      std::cout << "Invalid day, please choose a day between 1 and 2 or 0 to quit" << std::endl;
    }
  }
  return 0;
}
