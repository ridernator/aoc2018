#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#define INPUT "../data/input"

#define MAX_WORKERS 5
#define BASE_STEP_TIME 60

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

uint64_t workers = 0;

class Step {
    public:
        Step(const char name) : name(name),
                                completed(false),
                                inProgress(false),
                                timer(-1) {}

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

        bool isInProgress() {
            return inProgress;
        }

        void complete() {
            timer = BASE_STEP_TIME + (name - 64);
            inProgress = true;
        }

        void tick() {
            if (--timer == 0) {
                completed = true;
                inProgress = false;
                --workers;
            }
        }

    private:
        char name;

        std::set<Step*> befores;

        bool completed;

        bool inProgress;

        int64_t timer;
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

    uint64_t tickCount = 0;

    // While not all complete
    while ((std::size_t) std::count_if(steps.begin(), steps.end(), [] (const auto& value) {
        return value.second->isComplete();
    }) != steps.size()) {
        // Complete steps if able to complete
        for (auto& step : steps) {
            if ((!step.second->isComplete()) &&
                (!step.second->isInProgress()) &&
                (step.second->isReady()) &&
                (workers < MAX_WORKERS)) {
                step.second->complete();
                ++workers;
            }
        }

        // Tick all steps
        for (auto& step : steps) {
            step.second->tick();
        }

        ++tickCount;
    }

    std::cout << "Took " << tickCount << " ticks" << std::endl;

    for (const auto& letter : letters) {
        delete steps[letter];
    }    

    return 0;
}
