module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

export module Files;

namespace Files{
    export auto readFile(const std::filesystem::path &inputPath) -> std::vector<std::string> {
        std::ifstream file(inputPath);
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        return lines;
    }
}