# include <queue>
# include <string>
# include <iostream>

/*!
    Клас, който представлява дърво на Хъфман. Съдържа в себе си структура от върхове, които са върхове на дървото на Хъфман. 
*/
class huffmanTree
{
private:

    /*!
        @param root - указател към корена на дървото
        @param pq - приоритетна опашка от двойки, която съдържа в себе си върхове на дървото и техните тегла
        @param numOccur - масив, който съдържа броя на срещанията на всеки символ, честотната таблица
        @param code - масив, който съдържа кода на всеки символ
    */
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

    /*!
        @param str - низ, който ще се компресира
        @param out - изходен поток, в който ще се изведе компресираната версия на низа
        @return - връща броя на символите в компресирания низ
    */
    int compress(const std::string &str, std::ostream &out)  const;

    /*!
        @param str - низ, който ще се декомпресира
        @param size - броя на символите в некомпресирания низ
        @param out - изходен поток, в който ще се изведе декомпресираната версия на низа
        @return - връща декомпресирания низ
    */
    std::string decompress(const std::string &str, const int size, std::ostream &out) const;
    void print(std::ostream &out) const;
    void testPrint() const;
};

std::ostream& operator<<(std::ostream& out, const huffmanTree& tree);
