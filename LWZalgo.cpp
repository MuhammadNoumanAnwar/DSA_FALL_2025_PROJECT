#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> lzwCompress(const string &inputText)
{
    unordered_map<string, int> dictionary;
    int nextCode = 256;

    for (int i = 0; i < 256; i++)
        dictionary[string(1, char(i))] = i;

    vector<int> compressedCodes;
    string current = "";

    for (char ch : inputText)
    {
        string extended = current + ch;
        if (dictionary.count(extended))
            current = extended;
        else
        {
            compressedCodes.push_back(dictionary[current]);
            dictionary[extended] = nextCode++;
            current = string(1, ch);
        }
    }

    if (!current.empty())
        compressedCodes.push_back(dictionary[current]);

    return compressedCodes;
}
int main()
{
    string inputFile = "input.txt";
    string compressedFile = "compressed";
    string outputFile = "output.txt";
    
 return 0;
}