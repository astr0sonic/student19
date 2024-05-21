#include "eratosthenes.h"

using namespace std;

std::vector<int> sieve(int n) {
    int a[n];
    int v[n];
    for(int i=0;i<n;i++){
        a[i]=i;
        v[i]=i;
    }
    bool b[n];
    for(int i=0;i<n;i++){
        b[i]=true;
    }
    b[0]=false;
    b[1]=false;
    int kv;
    for(int i=2;i<pow(n,0.5);i++){
        if(a[i]!=0){
            kv = a[i];
        }
        else
            continue;
        for(int j=i+1;j<n;j++){
            if(a[j]!=0){
                if(a[j]%kv==0){
                    a[j]=0;
                    b[j]=false;
                }
            }
        }
    }
    std::vector<int> primes;
    for(int i=0;i<n;i++){
        if(b[i]==1)
            primes.push_back(v[i]);
    }
    return primes;
}
