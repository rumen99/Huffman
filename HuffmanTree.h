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

    void buildFreqTable(const std::string &);
    void buildTree();
    void buildCode(node*, std::string num);
    void printTree(node*, std::ostream &out) const;
    void deleteTree(node *);
    node* buildTree(std::istream &in);

public:
    huffmanTree(const std::string &);
    huffmanTree(std::istream &in);
    ~huffmanTree();
    int compress(const std::string &str, std::ostream &out)  const;
    std::string decompress(const std::string &str, const int size, std::ostream &out) const;
    void print(std::ostream &out) const;
    void testPrint() const;
};

std::ostream& operator<<(std::ostream& out, const huffmanTree& tree);
