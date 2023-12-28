# pragma once
# include "HuffmanTree.h"

huffmanTree::huffmanTree(std:: string &input)
{
    root = nullptr;
    for (int i = 0; i < 256; i++)
    {
        numOccur[i] = 0;
        code[i] = "";
    }
    buildFreqTable(input);
    buildTree();
    buildCode(root, "");
}

void huffmanTree::buildFreqTable(std:: string &input)
{
    for (int i = 0; i < input.length(); i++)
    {
        numOccur[input[i]]++;
    }

    for (int i = 0; i < 256; i++)
    {
        if (numOccur[i] > 0)
        {
            node *temp = new node;
            temp->weight = numOccur[i];
            temp->data = (char) i;
            temp->left = nullptr;
            temp->right = nullptr;
            pq.push(std::make_pair(-numOccur[i], temp));
        }
    }
}

void huffmanTree::buildTree()
{
    while (pq.size() > 1)
    {
        node *temp = new node;
        temp->left = pq.top().second;
        pq.pop();
        temp->right = pq.top().second;
        pq.pop();
        temp->data = '\0';
        temp->weight = temp->left->weight + temp->right->weight;
        pq.push(std::make_pair(-temp->weight, temp));
    }
    root = pq.top().second;
    pq.pop();
}

void huffmanTree::buildCode(node *root, std:: string num)
{
    if (root->left == nullptr && root->right == nullptr)
    {
        code[root->data] = num;
        return;
    }
    buildCode(root->left, (num+"0"));
    buildCode(root->right, (num+"1"));
}

std::string huffmanTree::compress(std::string str) const
{
    std::string output = "";
    int curr = 0;
    int bits = 0;

    for (int i = 0; i < str.length(); i++)
    {
        std::string temp = code[str[i]];
        for (int j = 0; j < temp.size(); j++){
            curr = curr << 1;
            if (temp[j] == '1')
            {
                curr = curr | 1;
            }
            bits++;
            if (bits == 8)
            {
                output += (char) curr;
                curr = 0;
                bits = 0;
            }
        }
    }

    if (bits > 0)
    {
        curr = curr << (8 - bits);
        output += (char) curr;
    }

    return output;
}

void huffmanTree::printTree(node *root, std::ostream &out) const
{
    /* https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree */
    if (root->left == nullptr && root->right == nullptr)
    {
        out << "1" << root->data;
        return;
    }
    out << "0"; 
    printTree(root->left, out);
    printTree(root->right, out);
}

void huffmanTree::print(std::ostream &out) const
{
    printTree(root, out);
    out << std::endl;
}

std::ostream& operator<<(std::ostream& out, const huffmanTree& tree)
{
    tree.print(out);
    return out;
}

void huffmanTree::deleteTree(huffmanTree::node *root)
{
    if (root == nullptr)
    {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

huffmanTree::~huffmanTree()
{
    deleteTree(root);
}

void huffmanTree::testPrint() const
{
    std::cout << "Test print" << std::endl;
    for (int i = 0; i < 256; i++)
    {
        if (numOccur[i] > 0)
        {
            std::cout << (char) i << " " << numOccur[i] << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Code" << std::endl;
    for (int i = 0; i < 256; i++)
    {
        if (code[i] != "")
        {
            std::cout << (char) i << " " << code[i] << std::endl;
        }
    }
    std::cout << std::endl;
}

huffmanTree::huffmanTree(std::istream &in)
{
    root = buildTree(in);
    return ;
}

huffmanTree::node* huffmanTree::buildTree(std::istream &in)
{
    char c;
    in >> c;
    if (c == '1')
    {
        in >> c;
        node *temp = new node;
        temp->data = c;
        temp->weight = 0;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }
    node *temp = new node;
    temp->left = buildTree(in);
    temp->right = buildTree(in);
    return temp;
}

std::string huffmanTree::decompress(std::string str, int size) const
{
    std::string output = "";
    node *curr = root;
    for (int i = 0; i < str.length() && output.size() < size; i++)
    {
        for (int j = 7; j >= 0 && output.size() < size; j--)
        {
            if ((str[i] >> j) & 1)
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
            if (curr->left == nullptr && curr->right == nullptr)
            {
                output += curr->data;
                curr = root;
            }
        }
    }
    return output;
}