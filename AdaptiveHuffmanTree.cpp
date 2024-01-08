# include "AdaptiveHuffmanTree.h"

adaptiveHuffmanTree::adaptiveHuffmanTree()
{
    root = nullptr;
    NYT = nullptr;
    for (int i = 0; i < 256; i++)
    {
        symbols[i] = nullptr;
    }
    root = new node();
    root->weight = 0;
    NYT = root;
    root->par = root->left = root->right = nullptr; 
}

std::string adaptiveHuffmanTree::binary_code (char c) {

    std::string output = "";
    int intValue = static_cast<int>(static_cast<unsigned char>(c));

    for (int i = 0; i < 8; i++)
    {
        output += ((intValue % 2) + '0');
        intValue /= 2;
    }
    std::reverse(output.begin(), output.end());
    return output;
}

std::string adaptiveHuffmanTree::code (node *temp) {
    std::string output = "";
    if (temp == root)
    {
        return "";
    }
    if (temp->par->left == temp)
    {
        output += "0";
    }
    else
    {
        output += "1";
    }
    return code(temp->par) + output;
}

void adaptiveHuffmanTree::recalc(node *temp) {
    while (temp->par != nullptr)
    {
        node *par = temp->par;
        if (par->left->weight > par->right->weight) {
            std :: swap (par->left, par->right);
        }
        par -> weight++;
        temp = par;
    }
}

adaptiveHuffmanTree::node* adaptiveHuffmanTree::addNode(char c) {
    node *temp = new node();
    temp->data = c;
    temp->weight = 1;
    temp->par = NYT;
    temp->left = nullptr;
    temp->right = nullptr;
    symbols[c] = temp;
    node *temp2 = new node();
    temp2->data = '\0';
    temp2->weight = 0;
    temp2->par = NYT;
    temp2->left = nullptr;
    temp2->right = nullptr;
    NYT->left = temp2;
    NYT->right = temp;
    NYT = temp2;
    return temp;
}
int adaptiveHuffmanTree::compress (const std::string& str, std::ostream &out)  {
    std::string output = "";
    
    for (int i = 0; i < str.length(); i++)
    {
        node *temp;
        if (symbols[str[i]] == nullptr)
        {
            temp = addNode(str[i]);
            output += code(NYT->par);
            output += binary_code(str[i]);
        }
        else
        {
            temp = symbols[str[i]];
            output += code(temp);
            temp->weight++;
        }
        recalc(temp);
    }

    std::string compressed_output = "";
    for (int i = 0; i < output.length(); i += 8) {
        std::string sub = output.substr(i, 8);
        char c = 0;
        for (int j = 0; j < 8; j++) {
            c <<= 1;
            c |= (sub[j] - '0');
        }
        compressed_output += c;
    }
    out << compressed_output;
    return compressed_output.size();

}

std::string adaptiveHuffmanTree::decompress(const std::string& str, const int& size, std::ostream &out){
    std::string output = "";
    node *curr = root;
    std::string binary_rep = "";
    for (int i = 0; i < str.length(); i++) {
        binary_rep += binary_code(str[i]);
    }
    for (int i = 0; i < binary_rep.length() && output.size() < size; i++)
    {
        if (curr->left != nullptr || curr->right != nullptr) {
            if (binary_rep[i] == '1')
            {
                curr = curr->right;
            }
            else
            {
                curr = curr->left;
            }
        } else {
            if (curr == NYT) {
                char ch = 0;
                for (int k = 0; k < 8; k++) {
                    ch <<= 1;
                    ch |= (binary_rep[i] == '1') & 1;
                    i ++;
                }
                i--;
                curr = addNode(ch);
                output += ch;
            } else {
                output += curr->data;
                curr->weight ++;
                i--; 
            }
            recalc(curr);
            curr = root;
        }
    }

    out << output;
    return output;
}

adaptiveHuffmanTree::~adaptiveHuffmanTree() {
    deleteTree(root);
}

void adaptiveHuffmanTree::deleteTree(node *temp) {
    if (temp == nullptr) {
        return;
    }
    deleteTree(temp->left);
    deleteTree(temp->right);
    delete temp;
}