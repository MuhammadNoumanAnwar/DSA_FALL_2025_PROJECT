# ACCEPTED
# DSA_FALL_2025_PROJECT
# File compression using Huffman encoding

|id|Name|
|-|-|
|K24-2522|Muhammad Muzammil Tanvir|
|K24-2543|Muhammad Nouman Anwar|

## Introduction
Our project mainly focuses on developing file compression system that reduces the size of text data without losing any information. The project will include different algorithms where we will compare the encoding efficiency based on frequency or patterns. The file compression system will read input files, then it will compress to binary format and later it will allow to decompress for verification of compressed data. Moreover, it will demonstrate how compression techniques can optimize storage usage and improve file transfer efficiency. The project will also compare the efficiency and effectiveness of different algorithms used in terms of compression ratio and frequency.

## Description
1-The program will create a program that is able to shrink the size of a file using a compression algorithm.

2-The program will then have the capability to restore (decompress) the same file back to its original size with no data lost.
Initially, the program will have one compression algorithm implemented to learn the basic idea behind file minimization.

3-Subsequently, the program will incorporate another algorithm to see which performs better and what results are produced.

4-The program will take text files as input and generate binary output files for compressed data.

5-The program will read file content, process character patterns or frequency, and compress data in an efficient manner.

6-While decompressing, the program will reverse the decoded binary data to readable text.

7-The primary emphasis will be placed on minimizing file size, preserving accuracy, and keeping the code modular so that more methods can be included later.

8-It will be a system coded in C++ with data structures such as trees, maps, heap and queues etc.

9-The program will test the project by comparing files reconstructed and original, examining compression ratios, and making sure that information is not lost.

## Data Structures that will be used
| Data Structure         | Purpose / Usage |
|------------------------|-----------------|
| Tree (Huffman Tree)    | Used to represent character codes based on their frequency for Huffman Encoding |
| Map (Character Map)    | Stores frequency count or mapping between characters and their codes. |
| Priority Queue (Min)   | Used to select nodes with lowest frequency while building Huffman Tree |
| Queue                  | Used during level-order traversal or decoding of encoded binary tree. |
| Stack                  | May be used for backtracking or reversing operations during encoding/decoding. |
| Array / String         | To store file content, binary data, or intermediate compressed sequences. |
| Hash Table / Unordered Map | For faster lookup of character-to-code or code-to-character mappings. |
| Linked List            | Can represent dynamic data nodes when simulating bit streams or dictionaries. |
| Heap                   | Used for building efficient priority queues in Huffman Encoding. |
| File Stream (fstream)  | Handles reading input files and writing compressed or decompressed data. |
