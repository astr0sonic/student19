#include "bracket.h"
#include <stack>
#include <cmath>
#include <string>

using namespace std;

bool checkBrackets(const std::string& s) {
    stack<string>m;
    
    int k1=0,k2=0,k3=0,k4=0;
    bool red=1;
    
    for(char c : s){
        if(c=='('){
            k1++;
            m.push("k1");
        }
        else if(c==')'){
            k1--;
            if(m.top()!="k1"){
                red=0;
                break;
            }
            else{
                m.pop();
            }
        }
        else if(c=='{'){
            k2++;
            m.push("k2");
        }
        else if(c=='}'){
            k2--;
            if(m.top()!="k2"){
                red=0;
                break;
            }
            else{
                m.pop();
            }
        }
        else if(c=='['){
            k3++;
            m.push("k3");
        }
        else if(c==']'){
            k3--;
            if(m.top()!="k3"){
                red=0;
                break;
            }
            else{
                m.pop();
            }
        }
        else if(c=='<'){
            k4++;
            m.push("k4");
        }
        else if(c=='>'){
            k4--;
            if(m.top()!="k4"){
                red=0;
                break;
            }
            else{
                m.pop();
            }
        }
    }
    
    if(k1==0 and k2==0 and k3==0 and k4==0 and red==1){
        return true;
    }
    else{
        return false;
    }
}
