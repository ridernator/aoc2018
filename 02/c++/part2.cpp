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
 * Read a file entirely into a vecor of strings
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

std::string getMatchingChars(const std::string& string1,
                             const std::string& string2) {
    std::string returnVal;

    for (decltype(string1.size()) index = 0; index < string1.size(); ++index) {
        if (string1[index] == string2[index]) {
            returnVal.push_back(string1[index]);
        }
    }

    return returnVal;
}

int main() {
    auto lines = readFileToVector();

    // Loop through all lines
    for (auto line1 = std::begin(lines); line1 != std::end(lines) - 1; ++line1) {
        // Loop through all lines after line1
        for (auto line2 = line1 + 1; line2 != std::end(lines); ++line2) {
            // Get common string
            std::string matchingChars = getMatchingChars(*line1, *line2);

            // If common string is only 1 char smaller than original string
            // then those were the matching strings
            if (matchingChars.size() == line1->size() - 1) {
                std::cout << "Common letters are " << matchingChars << std::endl;

                return 0;
            }
        }
    }

    return 1;
}
