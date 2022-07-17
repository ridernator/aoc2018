#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <cstddef>
#include <cinttypes>


#define INPUT "../data/input"

#define MAX_DISTANCE 10000

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

uint64_t calculateDistance(const int64_t x,
                           const int64_t y,
                           const std::pair<int64_t, int64_t> location) {
    return abs(location.first - x) + abs(location.second - y);
}

int main() {
    auto lines = readFileToVector();
    std::vector<std::pair<int64_t, int64_t>> locations;

    int64_t minX = std::numeric_limits<int64_t>::max();
    int64_t minY = std::numeric_limits<int64_t>::max();
    int64_t maxX = std::numeric_limits<int64_t>::min();
    int64_t maxY = std::numeric_limits<int64_t>::min();

    int64_t x;
    int64_t y;

    // Read in location and find min max
    for (const auto& line : lines) {
        sscanf(line.c_str(), "%" PRId64 ", %" PRId64, &x, &y);
        locations.push_back({x, y});

        minX = std::min(minX, x);
        minY = std::min(minY, y);
        maxX = std::max(maxX, x);
        maxY = std::max(maxY, y);
    }

    // Loop through every cell in min max and see if distance fits
    uint64_t numInRegion = 0;
    for (int64_t x = minX; x < maxX; ++x) {
        for (int64_t y = minY; y <= maxY; ++y) {
            uint64_t distanceSum = 0;

            for (const auto& location : locations) {
                distanceSum += calculateDistance(x, y, location);
            }
            
            if (distanceSum < 10000) {
                ++numInRegion;
            }
        }
    }

    std::cout << "Number of cells in region : " << numInRegion << std::endl;

    return 0;
}
