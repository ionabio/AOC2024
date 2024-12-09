module;
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>	

export module Day8;

namespace Day8 {
struct Position{
    int x;
    int y;
};
using Size = Position;
using Data = std::map<char, std::vector<Position>>;

auto parseInput(std::filesystem::path input_path){
    std::vector<std::string> lines;    
    std::ifstream file(input_path);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

auto parseData(auto& dataStr){
    Data data;
    for (int y = 0; y < dataStr.size(); ++y) {
        for (int x = 0; x < dataStr[y].size(); ++x) {
            if (dataStr[y][x] != '.' && dataStr[y][x] != '\n') {
                data[dataStr[y][x]].push_back({x, y});
            }
        }
    }
    return data;
}

export void solve(std::filesystem::path input_path){
 auto dataStr = parseInput(input_path);
 auto size  = Size(dataStr[0].size(), dataStr.size());
 auto data = parseData(dataStr);
 auto resultPart1 = 0;
}
}
