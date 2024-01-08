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

    /*!
        Извиква се при въвеждане на команда -c без -a. Компресира с нормалния алгоритъм на Хъфман.
        @param in - входен поток, от който ще се чете низа, който ще се компресира
        @param out - изходен поток, в който ще се извежда компресирания низ
        @param out_tree - изходен поток, в който ще се извежда дървото и дължината на низа
    */
    void compress(std::istream &in, std::ostream &out, std::ostream &out_tree);

    /*!
        Извиква се при въвеждане на команда -d без -a. Декомпресира с нормалния алгоритъм на Хъфман.
        @param in - входен поток, от който ще се чете низа, който ще се декомпресира
        @param in_tree - входен поток, от който ще се чете дървото и дължината на низа
        @param out - изходен поток, в който ще се извежда декомпресирания низ
        @param DEBUG - булева променлива, която показва дали да се извеждат символите на декомпресирания низ
    */
    void decompress(std::istream &in, std::istream &in_tree ,std::ostream &out, bool DEBUG);

    /*!
        Извиква се при въвеждане на команда -c с -a. Компресира с адаптивния алгоритъм на Хъфман.
        @param in - входен поток, от който ще се чете низа, който ще се компресира
        @param out - изходен поток, в който ще се извежда компресирания низ
        @param out_tree - изходен поток, в който ще се извежда само дължината на низа
    */
    void adaptive_compress(std::istream &in, std::ostream &out, std::ostream &out_tree);

    /*!
        Извиква се при въвеждане на команда -d с -a. Декомпресира с адаптивния алгоритъм на Хъфман.
        @param in - входен поток, от който ще се чете низа, който ще се декомпресира
        @param in_tree - входен поток, от който ще се чете дължината на низа
        @param out - изходен поток, в който ще се извежда декомпресирания низ
        @param DEBUG - булева променлива, която показва дали да се извеждат символите на декомпресирания низ
    */
    void adaptive_decompress(std::istream &in, std::istream &in_tree ,std::ostream &out, bool DEBUG);

public:
    void readLine();
    void print();
};