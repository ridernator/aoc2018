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
    std::map<uint64_t, std::pair<int64_t, int64_t>> locations;

    int64_t minX = std::numeric_limits<int64_t>::max();
    int64_t minY = std::numeric_limits<int64_t>::max();
    int64_t maxX = std::numeric_limits<int64_t>::min();
    int64_t maxY = std::numeric_limits<int64_t>::min();

    int64_t x;
    int64_t y;
    uint64_t index = 1;

    // Load data in
    for (const auto& line : lines) {
        sscanf(line.c_str(), "%" PRId64 ", %" PRId64, &x, &y);
        locations[index++] = {x, y};

        // Find rectangle min and maxs
        minX = std::min(minX, x);
        minY = std::min(minY, y);
        maxX = std::max(maxX, x);
        maxY = std::max(maxY, y);
    }

    int64_t gridWidth = (maxX + 1) - minX;
    int64_t gridHeight = (maxY + 1) - minY;

    // Initialise grid
    uint64_t** grid = new uint64_t*[gridWidth];

    for (int64_t x = 0; x < gridWidth; ++x) {
        *(grid + x) = new uint64_t[gridHeight];
    }

    // Populate grid
    for (int64_t x = minX; x <= maxX; ++x) {
        for (int64_t y = minY; y <= maxY; ++y) {
            uint64_t minNumber = 0;
            uint64_t minDistance = std::numeric_limits<uint64_t>::max();

            for (const auto& location : locations) {
                uint64_t distance = calculateDistance(x, y, location.second);

                if (distance < minDistance) {
                    minDistance = distance;
                    minNumber = location.first;
                } else if (distance == minDistance) {
                    minNumber = 0;
                }
            }

            grid[x - minX][y - minY] = minNumber;          
        }
    }

    // Make set of numbers around the edge
    std::set<uint64_t> edgeNumbers;
    for (int64_t x = 0; x < gridWidth; ++x) {
        edgeNumbers.insert(grid[x][0]);
        edgeNumbers.insert(grid[x][gridHeight - 1]);
    }
    for (int64_t y = 0; y < gridHeight; ++y) {
        edgeNumbers.insert(grid[0][y]);
        edgeNumbers.insert(grid[gridWidth - 1][y]);
    }

    // Remove locations who appear onthe edge
    std::erase_if(locations, [edgeNumbers] (const auto& item) {
        return edgeNumbers.find(item.first) != std::end(edgeNumbers);
    });

    std::map<uint64_t, uint64_t> sizes;
    for (const auto& location : locations) {
        sizes[location.first] = 0;
    }

    for (int64_t x = 0; x < gridWidth; ++x) {
        for (int64_t y = 0; y < gridHeight; ++y) {
            if (sizes.find(grid[x][y]) != std::end(sizes)) {
                ++sizes[grid[x][y]];
            }
        }
    }

    uint64_t maxSize = 0;
    for (const auto& size : sizes) {
        if (size.second > maxSize) {
            maxSize = size.second;
        }
    }

    std::cout << "Max non-infinite region : " << maxSize << std::endl;

    for (int64_t x = 0; x < gridWidth; ++x) {
        delete [] *(grid + x);
    }

    delete [] grid;

    return 0;
}
