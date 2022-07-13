#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

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

int main() {
    std::stringstream contents = readFile();
    std::string line;
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    uint64_t twoCount = 0;
    uint64_t threeCount = 0;
    uint64_t letterCount;
    bool twoFound;
    bool threeFound;

    // For each line in file
    while (std::getline(contents, line, '\n')) {
        twoFound = 0;
        threeFound = 0;

        // For each letter of the alphabet
        for (const char& letter : letters) {
            // Calculate number of times the letter exists in the string
            letterCount = std::count(line.begin(), line.end(), letter);

            // Flag if found twice or 3 times
            twoFound |= (letterCount == 2);
            threeFound |= (letterCount == 3);
        }

        // Increment counters if needed
        twoCount += twoFound ? 1 : 0;
        threeCount += threeFound ? 1 : 0;
    }

    std::cout << "Checksum = " << twoCount << " X " << threeCount << " = " << (twoCount * threeCount) << std::endl;

    return 0;
}
