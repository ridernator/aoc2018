#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <tuple>
#include <cstddef>
#include <string.h>

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

typedef struct {
    int32_t posX;
    int32_t posY;
    int32_t velX;
    int32_t velY;
} PV;

std::tuple<int32_t, int32_t, int32_t, int32_t> getMinMax(const std::vector<PV*> pvs) {
    int32_t minX = std::numeric_limits<int32_t>::max();
    int32_t minY = std::numeric_limits<int32_t>::max();
    int32_t maxX = std::numeric_limits<int32_t>::min();
    int32_t maxY = std::numeric_limits<int32_t>::min();

    for (const auto& pv : pvs) {
        minX = std::min(minX, pv->posX);
        minY = std::min(minY, pv->posY);
        maxX = std::max(maxX, pv->posX);
        maxY = std::max(maxY, pv->posY);
    }

    return {minX, minY, maxX, maxY};
}

void printGrid(const std::vector<PV*> pvs) {
    auto [minX, minY, maxX, maxY] = getMinMax(pvs);
    int32_t dimX = (maxX - minX) + 1;
    int32_t dimY = (maxY - minY) + 1;

    char** grid = new char*[dimY];

    for (int32_t row = 0; row < dimY; ++row) {
        *(grid + row) = new char[dimX];

        memset(*(grid + row), ' ', dimX);
    }

    for (const auto& pv : pvs) {
        grid[pv->posY - minY][pv->posX - minX] = '#';
    }

    for (int32_t row = 0; row < dimY; ++row) {
        for (int32_t col = 0; col < dimX; ++col) {
            fputc(*(*(grid + row) + col), stdout);
        }

        fputc('\n', stdout);
    }

    for (int32_t row = 0; row < dimY; ++row) {
        delete [] *(grid + row);
    }

    delete [] grid;
}

int main() {
    auto lines = readFileToVector();
    std::vector<PV*> pvs;

    for (const auto& line : lines) {
        PV* pv = new PV();
        sscanf(line.c_str(), "position=<%i,%i> velocity=<%i,%i>", &pv->posX, &pv->posY, &pv->velX, &pv->velY);
        pvs.push_back(pv);
    }

    uint32_t seconds = 0;
    
    // While height > 10
    while (true) {
        for (auto& pv : pvs) {
            pv->posX += pv->velX;
            pv->posY += pv->velY;
        }

        ++seconds;

        auto [minX, minY, maxX, maxY] = getMinMax(pvs);

        if ((maxY - minY) < 10) {
            printGrid(pvs);

            std::cout << "Took " << seconds << " seconds" << std::endl;
            
            // Pause
            fgetc(stdin);
        }
    }

    for (const auto& pv : pvs) {
        delete pv;
    }

    return 0;
}
