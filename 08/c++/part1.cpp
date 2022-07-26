#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#define INPUT "../data/input"

/**
 * Read a file entirely into a vector of ints
 * 
 * @param The name of the file to read
 * @return The vector of lines in the file
 **/
std::vector<uint32_t> readFileToVector(const std::string& filename = INPUT) {
    std::ifstream fileStream(filename);
    std::string string;
    std::vector<uint32_t> returnVal;
    
    while (std::getline(fileStream, string, ' ')) {
        returnVal.push_back(std::stol(string));
    }

    return returnVal;
}

typedef struct node {
    uint32_t numSubNodes;
    node** subNodes;

    uint32_t numMetaData;
    uint32_t* metaData;
} Node;

Node* createNode(const std::vector<uint32_t>& data,
                 uint32_t& index) {
    Node* node = new Node();

    node->numSubNodes = data[index++];
    node->numMetaData = data[index++];
    node->subNodes = new Node*[node->numSubNodes];
    node->metaData = new uint32_t[node->numMetaData];

    // Create subnodes
    for (uint32_t subNodeIndex = 0; subNodeIndex < node->numSubNodes; ++subNodeIndex) {
        node->subNodes[subNodeIndex] = createNode(data, index);
    }

    // Create metadata
    for (uint32_t metaDataIndex = 0; metaDataIndex < node->numMetaData; ++metaDataIndex) {
        node->metaData[metaDataIndex] = data[index++];
    }

    return node;
}

void countMetaData(const Node* node,
                   uint64_t& count) {
    // Recursively count metadata in subnodes
    for (uint32_t subNodeIndex = 0; subNodeIndex < node->numSubNodes; ++subNodeIndex) {
        countMetaData(node->subNodes[subNodeIndex], count);
    }

    // Add on count of metadata
    for (uint32_t metaDataIndex = 0; metaDataIndex < node->numMetaData; ++metaDataIndex) {
        count += node->metaData[metaDataIndex];
    }
}

void deleteNode(Node* node) {
    delete [] node->metaData;

    for (uint32_t subNodeIndex = 0; subNodeIndex < node->numSubNodes; ++subNodeIndex) {
        deleteNode(node->subNodes[subNodeIndex]);
    }

    delete node;
}

int main() {
    auto numbers = readFileToVector();

    // Create all nodes
    uint32_t index = 0;
    Node* head = createNode(numbers, index);

    // Count all metadata
    uint64_t count = 0;
    countMetaData(head, count);

    std::cout << "Total of metadata is " << count << std::endl;

    return 0;
}
