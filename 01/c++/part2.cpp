#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>

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
    int64_t frequency = 0;
    std::vector<int64_t> changes;
    std::set<int64_t> frequencies = {0};
    std::stringstream contents = readFile();
    std::string line;

    // Read frequency changes into a vector
    while (std::getline(contents, line, '\n')) {
        changes.push_back(std::stoll(line));
    }

    // Keep looping through changes till found
    while (true) {
        // For each frequency change
        for (const int64_t change : changes) {
            frequency += change;

            if (!frequencies.insert(frequency).second) {
                std::cout << "First frequency seen twice is " << frequency << "Hz" << std::endl;

                goto exit;
            }
        }
    }

    exit: return 0;
}
