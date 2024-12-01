
module;
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
export module Day1;

namespace Day1
{
    auto calculateDistance(auto leftSide, auto rightSide)
    {
        std::sort(leftSide.begin(), leftSide.end());
        std::sort(rightSide.begin(), rightSide.end());
        auto distance = 0;
        for (auto i = 0; i < leftSide.size(); ++i)
        {
            distance += std::abs(leftSide[i] - rightSide[i]);
        }
        return distance;
    }

    auto calculateSimilarity(const auto leftSide, const auto rightSide)
    {
        auto similarity = 0;
        std::for_each(leftSide.begin(), leftSide.end(), [&similarity, &rightSide](auto &i)
                      { 
                         auto numberOfOccurences = std::count(rightSide.begin(), rightSide.end(), i);                      
                          similarity += i * numberOfOccurences;
                      });
        return similarity;
    }

    export void solve(const std::filesystem::path &inputPath)
    {
        auto input = std::ifstream(inputPath);
        if (!input.is_open())
        {
            std::cerr << "Failed to open " << inputPath << "\n";
            return;
        }

        auto line = std::string();
        auto leftNumbers = std::vector<int>();
        auto rightNumbers = std::vector<int>();
        while (std::getline(input, line))
        {
            auto split = line.find(' ');
            auto first = std::stoi(line.substr(0, split));
            auto second = std::stoi(line.substr(split + 1));
            leftNumbers.push_back(first);
            rightNumbers.push_back(second);
        }

        std::cout << "Day 1 solution (Part A) the distances are: " << calculateDistance(leftNumbers, rightNumbers) << "\n";
        std::cout << "Day 1 solution (Part B) the similarities are: " << calculateSimilarity(leftNumbers, rightNumbers) << "\n";
    }
}
