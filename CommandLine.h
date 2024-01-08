# pragma once
# include <iostream>
# include <string>
# include <istream> 
# include <ostream>
# include <sstream>
# include <fstream>
# include "huffmanTree.h" 
# include "adaptiveHuffmanTree.h"

class commandLine
{
private:
    void compress(std::istream &in, std::ostream &out, std::ostream &out_tree);
    void decompress(std::istream &in, std::istream &in_tree ,std::ostream &out, bool DEBUG);
    void adaptive_compress(std::istream &in, std::ostream &out, std::ostream &out_tree);
    void adaptive_decompress(std::istream &in, std::istream &in_tree ,std::ostream &out, bool DEBUG);

public:
    void readLine();
    void print();
};