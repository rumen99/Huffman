# include <queue>
# include <string>
# include <iostream>
# include <algorithm>
class adaptiveHuffmanTree
{
private:
    /*!
        @param root - указател към корена на дървото
        @param NYT - указател към върха NYT
        @param symbols - масив, който съдържа указатели към всеки символ
    */
    struct node
    {
        char data;
        int weight;
        node *par;
        node *left;
        node *right;
    };
    node *root;
    node *NYT;
    node *symbols[256];

    std::string binary_code (char c);
    std::string code (node *temp);
    void deleteTree(node *);
    void recalc(node *temp);
    node* addNode(char c);

public:
    adaptiveHuffmanTree();
    ~adaptiveHuffmanTree();

    /*!
        @param str - низ, който ще се компресира
        @param out - изходен поток, в който ще се изведе компресираната версия на низа
        @return - връща броя на символите в компресирания низ
    */
    int compress(const std::string& str, std::ostream &out);

    /*!
        @param str - низ, който ще се декомпресира
        @param size - броя на символите в некомпресирания низ
        @param out - изходен поток, в който ще се изведе декомпресираната версия на низа
        @return - връща декомпресирания низ
    */
    std::string decompress(const std::string& str, const int& size, std::ostream &out);
};
