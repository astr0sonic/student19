#include "huffman.h"
#include <queue>
#include <map>
#include <string>

using namespace std;

struct Node{
    char ch;
    int freq;
    Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right){
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp{
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq;
    }
};

void eencode(Node* root, string str,map<char, string> &huffmanCode){
    if (root == nullptr)
        return;

    if (!root->left && !root->right){
        huffmanCode[root->ch] = str;
    }

    eencode(root->left, str + "0", huffmanCode);
    eencode(root->right, str + "1", huffmanCode);
}

void MtoTree(Node* root,map<char, string> &huffmanCode){
    for(auto c : huffmanCode){
        string q=c.second;
        for(char chh : q){
            if(chh=='0'){
                root->left = new Node;
                root->left;
            }
            else{
                root->right = new Node;
                root->right;
            }
        }
        root->ch=c.first;
    }
}

string ss="";

void ddecode(Node* root, int &index, string str){
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right){
        ss+=root->ch;
        return;
    }

    index++;

    if (str[index] =='0')
        ddecode(root->left, index, str);
    else
        ddecode(root->right, index, str);
}


std::string encode(const std::string& text) {
    map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;

    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1){
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top();    pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    Node* root = pq.top();

    map<char, string> huffmanCode;
    eencode(root, "", huffmanCode);

    string str = "";
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    string encoded=str;
    return encoded;
}

std::string decode(const std::string& encoded, std::map<char, std::string>& codes) {
    // Node* root;
    // root->left=nullptr; root->right=nullptr;
    // MtoTree(root,codes);
    // int index=-1;
    // while(index<(int)encoded.size()-2){
    //     ddecode(root,index,encoded);
    // }
    string str="";
    std::string decoded = "";
    for(char c : encoded){
        str+=c;
        for(auto cc : codes){
            if(cc.second==str){
                decoded+=cc.first;
                str="";
                break;
            }
        }
    }

    return decoded;
}
