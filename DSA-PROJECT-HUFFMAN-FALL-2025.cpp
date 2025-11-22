#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

class HuffmanNode
{
public:
    char data;
    int frequency;
    HuffmanNode *leftChild;
    HuffmanNode *rightChild;

    HuffmanNode(char character, int frequencyCount)
    {
        data = character;
        frequency = frequencyCount;
        leftChild = nullptr;
        rightChild = nullptr;
    }
};

class NodeComparator
{
public:
    bool operator()(HuffmanNode *firstNode, HuffmanNode *secondNode)
    {
        return firstNode->frequency > secondNode->frequency;
    }
};

class HuffmanCoder
{
public:
    unordered_map<char, string> huffmanCodeMap;

    void createHuffmanCodes(HuffmanNode *currentNode, string currentCode)
    {
        if (currentNode == nullptr)
            return;

        if (currentNode->leftChild == nullptr && currentNode->rightChild == nullptr)
        {
            huffmanCodeMap[currentNode->data] = currentCode;
            return;
        }

        createHuffmanCodes(currentNode->leftChild, currentCode + "0");
        createHuffmanCodes(currentNode->rightChild, currentCode + "1");
    }

    HuffmanNode *constructHuffmanTree(unordered_map<char, int> frequencyTable)
    {
        priority_queue<HuffmanNode *, vector<HuffmanNode *>, NodeComparator> minPriorityQueue;

        for (auto pair : frequencyTable)
        {
            HuffmanNode *newNode = new HuffmanNode(pair.first, pair.second);
            minPriorityQueue.push(newNode);
        }

        if (minPriorityQueue.size() == 1)
        {
            HuffmanNode *singleNode = minPriorityQueue.top();
            minPriorityQueue.pop();
            HuffmanNode *rootNode = new HuffmanNode('\0', singleNode->frequency);
            rootNode->leftChild = singleNode;
            return rootNode;
        }

        while (minPriorityQueue.size() > 1)
        {
            HuffmanNode *leftNode = minPriorityQueue.top();
            minPriorityQueue.pop();

            HuffmanNode *rightNode = minPriorityQueue.top();
            minPriorityQueue.pop();

            int combinedFrequency = leftNode->frequency + rightNode->frequency;
            HuffmanNode *parentNode = new HuffmanNode('\0', combinedFrequency);
            parentNode->leftChild = leftNode;
            parentNode->rightChild = rightNode;

            minPriorityQueue.push(parentNode);
        }

        return minPriorityQueue.top();
    }
int main()
{
    HuffmanCoder huffmanProcessor;

    huffmanProcessor.compressFile("input.txt", "compressed.bin");
    huffmanProcessor.decompressFile("compressed.bin", "output.txt");

    return 0;
}