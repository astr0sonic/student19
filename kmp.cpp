#include "kmp.h"

using namespace std;

std::vector<int> getIndices(const std::string& my_template, const std::string& text) {
    std::vector<int> result;
    string s = my_template + "#" + text;
    int n = (int)s.size();
    vector<int>p(n,0);
    for(int i=1;i<n;i++){
        int cur = p[i-1];
        while(s[i]!=s[cur] and cur>0){
            cur=p[cur-1];
        }
        if(s[i]==s[cur]){
            p[i]=cur+1;
        }
    }
    int iter=-1;
    for(int i=0;i<p.size();i++){
        if(p[i]==1){
            iter=i;
        }
        if(p[i]==(int)my_template.size()){
            result.push_back(iter-(int)my_template.size()-1);
        }
    }
    return result;
}
