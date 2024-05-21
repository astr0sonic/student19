#include "lzw.h"
#include <vector>
#include <unordered_map>

using namespace std;

std::vector<int> compress(const std::string& text) {
    unordered_map<string, int> dictionary;
    vector<int>m;
    for (int i = 0; i < 256; i++){
        string ch = "";
        ch += char(i);
        dictionary[ch] = i;
    }
    string w = "";
    char k;
    int dictSize = 256;

    for (auto &c : text){
        k = c;
        string wc = w + k;
        if (dictionary.find(wc) != dictionary.end()){
            w = wc;
        }
        else{
            m.push_back(dictionary[w]);
            dictionary[wc] = dictSize++;
            w = k;
        }
    }

    if (!w.empty()){
        m.push_back(dictionary[w]);
    }
    return m;
}

std::string decompress(const std::vector<int>& compressed) {
   unordered_map<int, string> dictionary;
    for (int i = 0; i < 256; i++) {
        string ch = "";
        ch += char(i);
        dictionary[i] = ch;
    }

    int dictSize = 256;
    int prevCode = compressed[0];
    string output = dictionary[prevCode];
    string entry;
    string w;

    for (int i = 1; i < compressed.size(); i++) {
        int currCode = compressed[i];
        if (dictionary.find(currCode) == dictionary.end()) {
            entry = dictionary[prevCode];
            entry += w[0];
        } else {
            entry = dictionary[currCode];
        }
        output += entry;
        w = entry;
        dictionary[dictSize++] = dictionary[prevCode] + entry[0];
        prevCode = currCode;
    }

    return output;
}
