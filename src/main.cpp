#include <filesystem>
#include <iostream>


// Import daily modules
import Day1;
import Day2;
import Day3;
import Day4;
import Day5;
import Day6;
import Day7;
import Day8;
import Day9;
import Day10;
int main(int argc, char *argv[]) {
  std::filesystem::path workingDir;
  if (argc < 2) {
    workingDir = std::filesystem::current_path() / ".." / "..";
  } else {
    workingDir = argv[1];
  }

  //choose a day to solve
  while(true){
    std::cout << "Choose a day to solve (1-7), 0 to quit : ";
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
    }else if (day == 3){
      Day3::solve(workingDir / "assets" / "3" / "input.txt");
      break;
    }else if (day == 4){
      Day4::solve(workingDir / "assets" / "4" / "input.txt");
      break;
    }
    else if (day == 5){
      Day5::solve(workingDir / "assets" / "5" / "input.txt");
      break;    
    }else if (day == 6){
      Day6::solve(workingDir / "assets" / "6" / "input.txt");
      break;
    }else if (day == 7){
      Day7::solve(workingDir / "assets" / "7" / "input.txt");
      break;
    }else if (day == 8){
      Day8::solve(workingDir / "assets" / "8" / "input.txt");
      break;
    }else if (day == 9){
      Day9::solve(workingDir / "assets" / "9" / "input.txt");
      break;
    }else if (day == 10){
      Day10::solve(workingDir / "assets" / "10" / "input.txt");
      break;
    }else{
      std::cout << "Invalid day, please choose a day between 1 and 7 or 0 to quit" << std::endl;
    }
  }
  return 0;
}
