#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;
class HuffmanNode{
public:
    char data;
    int frequency;
    HuffmanNode *leftChild;
    HuffmanNode *rightChild;
    HuffmanNode(char character, int frequencyCount){
        data = character;
        frequency = frequencyCount;
        leftChild = nullptr;
        rightChild = nullptr;
    }
};
class NodeComparator{
public:
    bool operator()(HuffmanNode *firstNode, HuffmanNode *secondNode){
        return firstNode->frequency > secondNode->frequency;
    }
};
class HuffmanCoder{
public:
    unordered_map<char, string> huffmanCodeMap;
    void createHuffmanCodes(HuffmanNode *currentNode, string currentCode)
    {
        if (currentNode == nullptr)
            return;
        if (currentNode->leftChild == nullptr && currentNode->rightChild == nullptr){
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
    void writeBinaryStream(ofstream &outputStream, string bitSequence){
        unsigned char byteBuffer = 0;
        int bitCount = 0;
        for(size_t i = 0; i < bitSequence.size(); i++){
            byteBuffer <<= 1;
            if(bitSequence[i] == '1'){
                byteBuffer |= 1;
            }
            bitCount++;
            if(bitCount == 8) {
                outputStream.write((char*)&byteBuffer, 1);
                byteBuffer = 0;
                bitCount = 0;
            }
        }
        if(bitCount > 0){
            byteBuffer <<= (8 - bitCount);
            outputStream.write((char*)&byteBuffer, 1);
        }
    }
    string readBinaryStream(ifstream &inputStream, int totalBitCount){
        string bitSequence;
        unsigned char byteBuffer;
        int bitsRead = 0;
        while(inputStream.read((char*)&byteBuffer, 1) && bitsRead < totalBitCount){
            for(int i = 7; i >= 0 && bitsRead < totalBitCount; i--){
                if((byteBuffer >> i) & 1){
                    bitSequence += '1';
                } 
                else{
                    bitSequence += '0';
                }
                bitsRead++;
            }
        }
        return bitSequence;
    }
 void compressFile(string inputFilename, string outputFilename)
    {
        ifstream inputFile(inputFilename, ios::binary);
        if (!inputFile)
        {
            cout << "Error: Cannot open input file." << endl;
            return;
        }

        string fileContent((istreambuf_iterator<char>(inputFile)), {});
        inputFile.close();

        unordered_map<char, int> frequencyTable;

        for (char character : fileContent)
        {
            frequencyTable[character]++;
        }

        HuffmanNode *rootNode = constructHuffmanTree(frequencyTable);
        createHuffmanCodes(rootNode, "");

        string encodedBitStream = "";

        for (char character : fileContent)
        {
            encodedBitStream += huffmanCodeMap[character];
        }

        ofstream outputFile(outputFilename, ios::binary);
        if (!outputFile)
        {
            cout << "Error: Cannot create output file." << endl;
            return;
        }

        int symbolCount = frequencyTable.size();
        outputFile.write((char *)&symbolCount, sizeof(int));

        for (auto entry : frequencyTable)
        {
            outputFile.write((char *)&entry.first, 1);
            outputFile.write((char *)&entry.second, sizeof(int));
        }

        int totalBits = encodedBitStream.length();
        outputFile.write((char *)&totalBits, sizeof(int));

        writeBinaryStream(outputFile, encodedBitStream);
        outputFile.close();
    }

    HuffmanNode *reconstructTreeFromFile(ifstream &inputFile)
    {
        int symbolCount;
        inputFile.read((char *)&symbolCount, sizeof(int));

        unordered_map<char, int> frequencyTable;

        for (int i = 0; i < symbolCount; i++)
        {
            char character;
            int frequency;
            inputFile.read((char *)&character, 1);
            inputFile.read((char *)&frequency, sizeof(int));
            frequencyTable[character] = frequency;
        }

        HuffmanNode *rootNode = constructHuffmanTree(frequencyTable);
        return rootNode;
    }
};
int main(){
    HuffmanCoder huffmanProcessor;
    huffmanProcessor.compressFile("input.txt", "compressed.bin");
    huffmanProcessor.decompressFile("compressed.bin", "output.txt");
    return 0;
}
