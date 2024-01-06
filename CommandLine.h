# pragma once
# include <iostream>
# include <string>
# include <istream> 
# include <ostream>
# include <sstream>
# include <fstream>
# include "huffmanTree.h" 

class commandLine
{
public:
    void readLine();
    void compress(std::istream &in, std::ostream &out, std::ostream &out_tree);
    void decompress(std::istream &in, std::istream &in_tree ,std::ostream &out, bool DEBUG);
    void print();
};