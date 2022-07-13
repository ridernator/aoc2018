#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>
#include <cinttypes>

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
    auto lines = readFileToVector();
    uint64_t claimId;
    uint64_t xOffset;
    uint64_t yOffset;
    uint64_t width;
    uint64_t height;
    std::array<std::array<uint64_t, 1000>, 1000> cloth;

    // Clear cloth array
    for (auto& array : cloth) {
        std::fill(std::begin(array), std::end(array), 0);
    }

    // For each line
    for (const auto& line : lines) {
        // Read in variables
        sscanf(line.c_str(), 
               "#%" PRIu64 " @ %" PRIu64 ",%" PRIu64 ": %" PRIu64 "x%" PRIu64,
               &claimId, &xOffset, &yOffset, &width, &height);
    
        // Fill in area
        for (uint64_t y = yOffset; y < yOffset + height; ++y) {
            for (uint64_t x = xOffset; x < xOffset + width; ++x) {
                ++cloth[y][x];
            }
        }
    }

    // For each line
    for (const auto& line : lines) {
        bool failed = false;

        // Read in variables
        sscanf(line.c_str(), 
               "#%" PRIu64 " @ %" PRIu64 ",%" PRIu64 ": %" PRIu64 "x%" PRIu64,
               &claimId, &xOffset, &yOffset, &width, &height);
    
        // Check if all 1s in area
        for (uint64_t y = yOffset; y < yOffset + height; ++y) {
            for (uint64_t x = xOffset; x < xOffset + width; ++x) {
                if (cloth[y][x] != 1) {
                    failed = true;

                    break;
                }
            }

            if (failed) {
                break;
            }
        }

        if (!failed) {
            break;
        }
    }

    std::cout << "Claim with no overlaps is claim number " << claimId << std::endl;

    return 0;
}
