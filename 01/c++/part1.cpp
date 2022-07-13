#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

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
    int64_t frequency = 0;

    // For each line in file
    while (std::getline(contents, line, '\n')) {
        // Increase frequency by value in the line
        frequency += std::stoll(line);
    }

    std::cout << "Resulting frequency is " << frequency << "Hz" << std::endl;

    return 0;
}
