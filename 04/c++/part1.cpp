#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <array>
#include <algorithm>
#include <cinttypes>
#include <iomanip>

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
    auto unsortedLines = readFileToVector();
    std::map<std::time_t, std::string> lines;
    uint64_t guard;

    for (const auto& line : unsortedLines) {
        std::tm tm;
        std::istringstream ss(line);
        ss >> std::get_time(&tm, "[%Y-%m-%d %H:%M]");
        lines[std::mktime(&tm)] = line.substr(line.find(']') + 2);
        std::cout << tm.tm_min << " " << std::mktime(&tm) << " " << line.substr(line.find(']') + 2) << std::endl;
    }

    for (const auto& entry : lines) {
        // std::size_t hashPos = entry.second.find('#');
        // if (hashPos != std::string::npos) {
        //     sscanf(entry.second.substr(hashPos).c_str(),
        //            "#%" PRIu64,
        //            &guard);
        // }

        std::cout << guard << " " << entry.first << " " << entry.second << std::endl;
    }

    return 0;
}


        // std::size_t hashPos = line.find('#');
        // if (hashPos != std::string::npos) {
        //     sscanf(line.substr(hashPos).c_str(),
        //            "#%" PRIu64,
        //            &guard);