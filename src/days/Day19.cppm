module;

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <filesystem>
#include <unordered_set>
#include <algorithm>


export module Day19;

import Files;

namespace Day19 {

// Helper function to split string by delimiter
std::vector<std::string> split(const std::string& str, char delim) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        if (!token.empty()) {  // Skip empty tokens
            tokens.push_back(token);
        }
    }
    return tokens;
}

// Check if a design can be made with available patterns
bool canMakeDesign(const std::string& design, const std::unordered_set<std::string>& patterns) {
    // Base case: empty design is always possible
    if (design.empty()) return true;
    
    // Try each pattern at the start of the design
    for (const auto& pattern : patterns) {
        if (design.length() >= pattern.length() && 
            design.substr(0, pattern.length()) == pattern) {
            // If this pattern matches the start of the design,
            // recursively check if we can make the rest
            if (canMakeDesign(design.substr(pattern.length()), patterns)) {
                return true;
            }
        }
    }
    return false;
}

export void solve(std::filesystem::path input) {
    auto lines = Files::readFile(input);
    
    // Parse patterns from first line
    std::unordered_set<std::string> patterns;
    auto patternTokens = split(lines[0], ',');
    for (auto& pattern : patternTokens) {
        // Remove any whitespace
        pattern.erase(std::remove_if(pattern.begin(), pattern.end(), isspace), pattern.end());
        patterns.insert(pattern);
    }
    
    // Process designs (skip first two lines - patterns and blank line)
    int possibleDesigns = 0;
    for (size_t i = 2; i < lines.size(); i++) {
        auto design = lines[i];
        // Remove any whitespace
        design.erase(std::remove_if(design.begin(), design.end(), isspace), design.end());
        
        if (canMakeDesign(design, patterns)) {
            possibleDesigns++;
        }
    }
    
    std::cout << "Number of possible designs (Part 1): " << possibleDesigns << std::endl;
}

}