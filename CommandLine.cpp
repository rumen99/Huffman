#include "CommandLine.h"
void commandLine::readLine()
{
    std::string input;
    std::getline(std::cin, input);
    enum { COMPRESS, DECOMPRESS, NONE, EXIT } state = NONE;
    
    std::string inputFile = "";
    std::string outputFile = "";
    
    size_t pos = 0;
    bool DEBUG = false;
    bool adaptive = false;
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
        } else if (option == "-h") {
            std::cout << "Usage: -c -i <input file> -o <output file> [-a]" << std::endl;
            std::cout << "       -d -i <input file> -o <output file> [-p] [-a]" << std::endl;
            std::cout << "       -h" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  -a: adaptive" << std::endl;
            std::cout << "  -c: compress" << std::endl;
            std::cout << "  -d: decompress" << std::endl;
            std::cout << "  -i: input file" << std::endl;
            std::cout << "  -o: output file" << std::endl;
            std::cout << "  -p: print debug info" << std::endl;
            std::cout << "  -h: help" << std::endl;
            std::cout << "  -e: exit" << std::endl;
            return;
        } else if (option == "-e") {
            state = EXIT;
            return;
        } else if (option == "-a") {
            adaptive = true;
        } else {
            std::cout << "Invalid option. Try -h for more information!" << option << std::endl;
            return;
        }


        input.erase(0, pos + 2);
    }
    
    if (state == EXIT) {
        std::cout << "Exiting..." << std::endl;
        exit(0);
        return;
    }


    if (state != NONE && !inputFile.empty() && !outputFile.empty()) {
        std :: ifstream in;
        in.open(inputFile, std::ios::binary);
        std::ofstream out(outputFile, std::ios::binary);

        if (!in) {
            std::cout << "Input file " << inputFile << " does not exist" << std::endl;
            return;
        }

        if (!out) {
            std::cout << "Output file could not be created" << std::endl;
            return;
        }

        if (state == COMPRESS) {
            std::ofstream out_tree(outputFile + ".tree");
            if (adaptive)
                adaptive_compress(in, out, out_tree);
            else
                compress(in, out, out_tree);
        } else {
            std::ifstream in_tree(inputFile + ".tree");
            if (!in_tree) {
                std::cout << "Tree file " << inputFile << ".tree does not exist" << std::endl;
                return;
            }
            if (adaptive)
                adaptive_decompress(in, in_tree, out, DEBUG);
            else
                decompress(in, in_tree, out, DEBUG);
        }
    } else{
        std::cout << "Invalid input. Try -h for more information" << std::endl;
        return ;
    }
}

void commandLine::compress(std::istream &in, std::ostream &out, std::ostream &out_tree)
{
    std::string input((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    huffmanTree tree(input);
    int size = tree.compress(input, out);
    out_tree << tree;
    out_tree << input.size() << std::endl;
    double ratio = (double) size / input.size();
    std :: cout << "Compressed successfully! Compressed/Original ratio: " << ratio << std :: endl;
}

void commandLine::adaptive_compress(std::istream &in, std::ostream &out, std::ostream &out_tree)
{
    std::string input((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    adaptiveHuffmanTree tree;
    int size = tree.compress(input, out);
    out_tree << input.size() << std::endl;
    double ratio = (double) size / input.size();
    std :: cout << "Compressed successfully! Compressed/Original ratio: " << ratio << std :: endl;
}

void commandLine::decompress(std::istream &in, std::istream &in_tree, std::ostream &out,bool DEBUG)
{
    huffmanTree tree(in_tree);
    int size;
    in_tree>>size;
    std::string input((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::string decompressed = tree.decompress(input, size, out);
    if (DEBUG) {
        for (char ch : decompressed) {
            std::cout << (int) ch << " ";
        }
        std::cout << std::endl;
    }
    std :: cout << "Decompressed successfully!" << std :: endl;
}

void commandLine::adaptive_decompress(std::istream &in, std::istream &in_tree, std::ostream &out,bool DEBUG)
{
    adaptiveHuffmanTree tree;
    int size;
    in_tree>>size;
    std::string input((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::string decompressed = tree.decompress(input, size, out);
    if (DEBUG) {
        for (char ch : decompressed) {
            std::cout << (int) ch << " ";
        }
        std::cout << std::endl;
    }
    std :: cout << "Decompressed successfully!" << std :: endl;
}