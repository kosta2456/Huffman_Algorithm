#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_
#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<map>
#include<queue>
#include <string>

using namespace std;

struct Node {
public:
    int count = 0;
    char letter;
    Node* left = NULL;
    Node* right = NULL;
};


struct cmp{
    bool operator()(Node* one, Node* two) {
        return (one->count > two->count);
    }
};

class huffman_tree {
public:
    priority_queue<Node*,vector<Node*>,cmp> huffTree;
    huffman_tree(const string &file_name);
    ~huffman_tree();
    string get_character_code(char character) const;
    string encode(const string &file_name) const;
    string decode(const string &string_to_decode) const;
    void tree(Node *head, string null) const;
    string filenew(string file) const;

};



#endif
