# pragma once
# include <iostream>
# include <string>
# include <istream> 
# include <ostream>
# include "huffmanTree.h" 

class commandLine
{
public:
    void readLine();
    void compress(std::istream &in, std::ostream &out);
    void decompress(std::istream &in, std::ostream &out, bool DEBUG);
    void print();
};