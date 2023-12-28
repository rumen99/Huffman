#include "CommandLine.h"
#include <fstream>

void commandLine::readLine()
{
    std::string input;
    std::getline(std::cin, input);
    enum { COMPRESS, DECOMPRESS, NONE } state = NONE;
    
    std::string inputFile = "";
    std::string outputFile = "";
    
    size_t pos = 0;
    bool DEBUG = false;
    while ((pos = input.find("-")) != std::string::npos) {
        std::string option = input.substr(pos, 2);
        if (option == "-c") {
            state = COMPRESS;
        } else if (option == "-d") {
            state = DECOMPRESS;
        } else if (option == "-i") {
            inputFile = input.substr(pos + 3);
            size_t spacePos = inputFile.find(' ');
            if (spacePos != std::string::npos) {
                inputFile = inputFile.substr(0, spacePos);
            }
        } else if (option == "-o") {
            outputFile = input.substr(pos + 3);
            size_t spacePos = outputFile.find(' ');
            if (spacePos != std::string::npos) {
                outputFile = outputFile.substr(0, spacePos);
            }
        } else if (option == "-p") {
            DEBUG = true;
        }
        input.erase(0, pos + 2);
    }
    


    if (state != NONE && !inputFile.empty() && !outputFile.empty()) {
        std::ifstream in(inputFile);
        std::ofstream out(outputFile);

        if (!in) {
            std::cout << "Input file " << inputFile << " does not exist" << std::endl;
            return;
        }

        if (!out) {
            std::cout << "Output file could not be created" << std::endl;
            return;
        }

        if (state == COMPRESS) {
            compress(in, out);
        } else {
            decompress(in, out, DEBUG);
        }
    } else{
        std::cout << "Invalid input" << std::endl;
        return ;
    }
}

void commandLine::compress(std::istream &in, std::ostream &out)
{
    std::string input;
    in>>input;
    huffmanTree tree(input);
    std::string compressed = tree.compress(input);
    out << tree;
    out << input.size() << std::endl;
    out << compressed;
    double ratio = (double) compressed.size() / input.size();
    std :: cout << "Compressed successfully! Compressed/Original ratio: " << ratio << std :: endl;
}

void commandLine::decompress(std::istream &in, std::ostream &out, bool DEBUG)
{
    huffmanTree tree(in);
    std::string input;
    int size;
    in>>size;
    in>>input;
    std::string decompressed = tree.decompress(input, size);
    if (DEBUG) {
        for (char ch : decompressed) {
            std::cout << (int) ch << " ";
        }
        std::cout << std::endl;
    }
    
    out << decompressed;
    std :: cout << "Decompressed successfully!" << std :: endl;
}