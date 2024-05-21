#include "max_value.h"
#include <algorithm>

using namespace std;


double calculateMaxValue(double* nums, int n) {
    double varr[8];
    double max=nums[0];
    double min=nums[0];

    for(int i=1;i<n;i++){
        varr[0]=max+nums[i];
        varr[1]=max-nums[i];
        varr[2]=max*nums[i];
        if(nums[i]!=0){
            varr[3]=max/nums[i];
            varr[7]=min/nums[i];
        }
        else {
            varr[3]=0;
            varr[7]=0;
        }
        varr[4]=min+nums[i];
        varr[5]=min-nums[i];
        varr[6]=min*nums[i];
        varr[7]=min/nums[i];
        pair<double*,double*> minmax=minmax_element(begin(varr),end(varr));
        min=*minmax.first;
        max=*minmax.second;
    }

    return max;
}
