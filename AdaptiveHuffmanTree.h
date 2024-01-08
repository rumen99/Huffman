# include <queue>
# include <string>
# include <iostream>
# include <algorithm>
class adaptiveHuffmanTree
{
private:
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
    int compress(const std::string& str, std::ostream &out);
    std::string decompress(const std::string& str, const int& size, std::ostream &out);
};
