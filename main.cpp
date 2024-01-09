// #define TESTMODE


#ifndef TESTMODE

# include <iostream>
# include <string>
# include "CommandLine.h"

int main(){
    commandLine cmd;
    while(true)
        cmd.readLine();
    return 0;
}

#endif

#ifdef TESTMODE

# include <iostream>
# include <string>
# include <fstream>
# include "huffmanTree.h"
# include "adaptiveHuffmanTree.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Huffman test_1") {
    std::ifstream in("test_1", std::ios::binary);
    std::ofstream out("test_1_compressed", std::ios::binary);
    std::ofstream out_tree("test_1.tree");
    
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    huffmanTree tree(input);
    int size = tree.compress(input, out);
    out_tree << tree;
    out_tree << input.size();
    in.close();
    out.close();
    out_tree.close();

    std::ifstream in_tree("test_1.tree");
    std::ifstream in_compressed("test_1_compressed", std::ios::binary);
    std::ofstream out_decompressed("test_1_decompressed", std::ios::binary);
    huffmanTree tree2(in_tree);
    int sz;
    in_tree >> sz;
    std::ostringstream ss2;
    ss2 << in_compressed.rdbuf();
    std :: string compressed = ss2.str();
    std::string output = tree2.decompress(compressed, sz, out_decompressed);
    CHECK (output == input);
}

TEST_CASE("Huffman test_2") {
    std::ifstream in("test_2", std::ios::binary);
    std::ofstream out("test_2_compressed", std::ios::binary);
    std::ofstream out_tree("test_2.tree");
    
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    huffmanTree tree(input);
    int size = tree.compress(input, out);
    out_tree << tree;
    out_tree << input.size();
    in.close();
    out.close();
    out_tree.close();

    std::ifstream in_tree("test_2.tree");
    std::ifstream in_compressed("test_2_compressed", std::ios::binary);
    std::ofstream out_decompressed("test_2_decompressed", std::ios::binary);
    huffmanTree tree2(in_tree);
    int sz;
    in_tree >> sz;
    std::ostringstream ss2;
    ss2 << in_compressed.rdbuf();
    std :: string compressed = ss2.str();
    std::string output = tree2.decompress(compressed, sz, out_decompressed);
    CHECK (output == input);
}

TEST_CASE("Huffman dickens") {
    std::ifstream in("dickens", std::ios::binary);
    std::ofstream out("dickens_compressed", std::ios::binary);
    std::ofstream out_tree("dickens.tree");
    
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    huffmanTree tree(input);
    int size = tree.compress(input, out);
    out_tree << tree;
    out_tree << input.size();
    in.close();
    out.close();
    out_tree.close();

    std::ifstream in_tree("dickens.tree");
    std::ifstream in_compressed("dickens_compressed", std::ios::binary);
    std::ofstream out_decompressed("dickens_decompressed", std::ios::binary);
    huffmanTree tree2(in_tree);
    int sz;
    in_tree >> sz;
    std::ostringstream ss2;
    ss2 << in_compressed.rdbuf();
    std :: string compressed = ss2.str();
    std::string output = tree2.decompress(compressed, sz, out_decompressed);
    CHECK (output == input);
}

TEST_CASE("Adaptive Huffman test_1") {
    std::ifstream in("test_1", std::ios::binary);
    std::ofstream out("test_1_compressed", std::ios::binary);
    std::ofstream out_tree("test_1.tree");
    
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    adaptiveHuffmanTree tree;
    int size = tree.compress(input, out);
    out_tree << input.size();
    in.close();
    out.close();
    out_tree.close();

    std::ifstream in_tree("test_1.tree");
    std::ifstream in_compressed("test_1_compressed", std::ios::binary);
    std::ofstream out_decompressed("test_1_decompressed", std::ios::binary);
    adaptiveHuffmanTree tree2;
    int sz;
    in_tree >> sz;
    std::ostringstream ss2;
    ss2 << in_compressed.rdbuf();
    std :: string compressed = ss2.str();
    std::string output = tree2.decompress(compressed, sz, out_decompressed);
    CHECK (output == input);
}

TEST_CASE("Adaptive Huffman test_2") {
    std::ifstream in("test_2", std::ios::binary);
    std::ofstream out("test_2_compressed", std::ios::binary);
    std::ofstream out_tree("test_2.tree");
    
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    adaptiveHuffmanTree tree;
    int size = tree.compress(input, out);
    out_tree << input.size();
    in.close();
    out.close();
    out_tree.close();

    std::ifstream in_tree("test_2.tree");
    std::ifstream in_compressed("test_2_compressed", std::ios::binary);
    std::ofstream out_decompressed("test_2_decompressed", std::ios::binary);
    adaptiveHuffmanTree tree2;
    int sz;
    in_tree >> sz;
    std::ostringstream ss2;
    ss2 << in_compressed.rdbuf();
    std :: string compressed = ss2.str();
    std::string output = tree2.decompress(compressed, sz, out_decompressed);
    CHECK (output == input);
}

TEST_CASE("Adaptive Huffman dickens") {
    std::ifstream in("dickens", std::ios::binary);
    std::ofstream out("dickens_compressed", std::ios::binary);
    std::ofstream out_tree("dickens.tree");
    
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();
    adaptiveHuffmanTree tree;
    int size = tree.compress(input, out);
    out_tree << input.size();
    in.close();
    out.close();
    out_tree.close();

    std::ifstream in_tree("dickens.tree");
    std::ifstream in_compressed("dickens_compressed", std::ios::binary);
    std::ofstream out_decompressed("dickens_decompressed", std::ios::binary);
    adaptiveHuffmanTree tree2;
    int sz;
    in_tree >> sz;
    std::ostringstream ss2;
    ss2 << in_compressed.rdbuf();
    std :: string compressed = ss2.str();
    std::string output = tree2.decompress(compressed, sz, out_decompressed);
    CHECK (output == input);
}

#endif