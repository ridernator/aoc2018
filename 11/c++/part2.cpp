#include <iostream>
#include <limits>
#include <cstddef>

const uint32_t DIMENSION=300;
const int32_t GRID_SERIAL_NUMBER=7315;

int main() {
    int32_t rackId;
    int32_t powerLevel;
    int32_t** grid = new int32_t*[DIMENSION];

    for (uint32_t row = 0; row < DIMENSION; ++row) {
        *(grid + row) = new int32_t[DIMENSION];

        for (uint32_t col = 0; col < DIMENSION; ++col) {
            // Perform calculation to get power level
            rackId = (col + 1 + 10);
            powerLevel = rackId;
            powerLevel *= (row + 1);
            powerLevel += GRID_SERIAL_NUMBER;
            powerLevel *= rackId;
            powerLevel /= 100;
            powerLevel %= 10;
            powerLevel -= 5;

            *(*(grid + row) + col) = powerLevel;
        }
    }

    int32_t power;
    int32_t mostPower = std::numeric_limits<int32_t>::min();
    uint32_t bestX = 0;
    uint32_t bestY = 0;
    uint32_t bestN = 0;

    // Loop through all possible NxN squares to find best solution
    for (uint32_t N = 1; N < 300; ++N) {
        for (uint32_t row = 0; row < DIMENSION - N; ++row) {
            for (uint32_t col = 0; col < DIMENSION - N; ++col) {
                power = 0;

                for (uint32_t y = row; y < row + N; ++y) {
                    for (uint32_t x = col; x < col + N; ++x) {
                        power += *(*(grid + y) + x);
                    }
                }

                if (power > mostPower) {
                    mostPower = power;
                    bestX = col + 1;
                    bestY = row + 1;
                    bestN = N;
                }
            }
        }
    }

    std::cout << "Best location (top-left) is " << bestX << "," << bestY << "," << bestN << " with total power of " << mostPower << std::endl;

    for (uint32_t row = 0; row < DIMENSION; ++row) {
        delete [] *(grid + row);
    }

    delete [] grid;

    return 0;
}
