#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <limits>

#define INPUT "../data/input"

/**
 * Read a file entirely into a stringstream
 * 
 * @param The name of the file to read
 * @return The contents of the file
 **/
std::stringstream readFile(const std::string& filename = INPUT) {
    std::ifstream fileStream(filename);
    std::stringstream returnVal;
    
    returnVal << fileStream.rdbuf();

    return returnVal;
}

/**
 * Read a file entirely into a vector of strings
 * 
 * @param The name of the file to read
 * @return The vector of lines in the file
 **/
std::vector<std::string> readFileToVector(const std::string& filename = INPUT) {
    std::ifstream fileStream(filename);
    std::string string;
    std::vector<std::string> returnVal;
    
    while (std::getline(fileStream, string)) {
        returnVal.push_back(string);
    }

    return returnVal;
}

int main() {
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    std::vector<std::string> polymers = readFileToVector();
    std::string polymer;
    uint64_t shortestLength;
    bool simplified;
    
    for (auto originalPolymer : polymers) {
        // Default shortest length to huge
        shortestLength = std::numeric_limits<uint64_t>::max();
        
        // For each letter of the alphabet
        for (const auto& letter : letters) {
            // Construct th polymer with out that letter
            polymer = originalPolymer;
            polymer.erase(std::remove(std::begin(polymer), std::end(polymer), letter), std::end(polymer));
            polymer.erase(std::remove(std::begin(polymer), std::end(polymer), std::toupper(letter)), std::end(polymer));
            
            // See how far it can be simplified
            while (true) {
                simplified = false;
                
                for (decltype(polymer.size()) index = 0; index < polymer.size() - 1; ++index) {
                    // Strip out opposite symbols
                    if ((polymer[index] == polymer[index + 1] + 32) || 
                        (polymer[index] == polymer[index + 1] - 32)) {                        
                        polymer = polymer.erase(index, 2);

                        simplified = true;
                    }
                }

                if (!simplified) {
                    break;
                }
            }

            shortestLength = std::min(shortestLength, polymer.size());
        }

        std::cout << "Simplest polymer is " << shortestLength << " long" << std::endl;
    }

    return 0;
}
