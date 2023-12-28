# include <queue>
# include <string>
# include <iostream>
class huffmanTree
{
private:
    struct node
    {
        char data;
        int weight;
        node *left;
        node *right;
    };
    node *root;
    std::priority_queue <std:: pair < int, node*> > pq;
    int numOccur[256];
    std::string code[256];

    void buildFreqTable(std::string &);
    void buildTree();
    void buildCode(node *, std::string num);
    void printTree(node *, std::ostream &out) const;
    void deleteTree(node *);
    node* buildTree(std::istream &in);

public:
    huffmanTree(std::string &);
    huffmanTree(std::istream &in);
    ~huffmanTree();
    std::string compress(std::string str)  const;
    std::string decompress(std::string str, int size) const;
    void print(std::ostream &out) const;
    void testPrint() const;
};

std::ostream& operator<<(std::ostream& out, const huffmanTree& tree);
