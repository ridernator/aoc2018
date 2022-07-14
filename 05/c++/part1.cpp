#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

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
    std::vector<std::string> polymers = readFileToVector();
    bool simplified;
    
    for (auto polymer : polymers) {
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

        std::cout << "Simplified polymer is " << polymer.size() << " long" << std::endl;
    }

    return 0;
}
