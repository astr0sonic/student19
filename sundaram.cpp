#include "sundaram.h"
#include <cmath>

using namespace std;

std::vector<int> sieve(int n) {
    std::vector<int> primes;
    int a[n];
    for(int q=0;q<n;q++){
        a[q]=q;
    }
    for(int i=1;i<=(pow(2*n+1,0.5)-1)/2;i++){
        for(int j=i;j<=(n-i)/(2*i+1);j++){
            a[i+j+2*i*j]=0;
        }

    }
    primes.push_back(2);
    for(int y=0;a[y]*2+1<=n;y++){
        if (a[y]!=0){
            primes.push_back(a[y]*2+1);
        }
    }
    return primes;
}
