#include <iostream>
#include <filesystem>
#include <string>

// Import daily modules
import Day1;
// Add more imports as needed

int main(int argc, char* argv[]) {
    std::filesystem::path workingDir;
    if (argc < 2) {
        workingDir = std::filesystem::current_path() / ".." / "..";
    }else {
        workingDir = argv[1];
    }     

    // Example usage of Day1 module
    Day1::solve(workingDir / "assets" / "1" / "input.txt");

    return 0;
}
