#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
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

class Step {
    public:
        Step(const char name) : name(name),
                                completed(false) {}

        char getName() {
            return name;
        }

        void addBefore(Step* step) {
            befores.insert(step);
        }

        // A step is ready to do if all the before steps are complete
        bool isReady() {
            bool returnVal = true;

            for (const auto& before : befores) {
                returnVal &= before->isComplete();
            }

            return returnVal;
        }

        bool isComplete() {
            return completed;
        }

        void complete() {
            completed = true;
        }

    private:
        char name;

        std::set<Step*> befores;

        bool completed;
};

int main() {
    std::map<char, Step*> steps;
    std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Init steps
    for (const auto& letter : letters) {
        steps[letter] = new Step(letter);
    }

    // read in steps
    for (const auto& line : readFileToVector()) {
        char a;
        char b;

        sscanf(line.c_str(), "Step %c must be finished before step %c", &a, &b);
        steps[b]->addBefore(steps[a]);
    }

    // While not all complete
    while ((std::size_t) std::count_if(steps.begin(), steps.end(), [] (const auto& value) {
        return value.second->isComplete();
    }) != steps.size()) {
        // Complete steps if able to complete
        for (auto& step : steps) {
            if ((!step.second->isComplete()) &&
                (step.second->isReady())) {
                step.second->complete();
                std::cout << step.first;

                break;
            }
        }
    }

    std::cout << std::endl;

    for (const auto& letter : letters) {
        delete steps[letter];
    }    

    return 0;
}
