#include "volume.h"
#include <algorithm>

int getMaxVolume(int a, int b, int c, int n, int* arr){
    int maxVolume = 0;
    int q;
    for (int startColumn = 0; startColumn < n; ++startColumn){
        for (int endColumn = startColumn + 1; endColumn < n; ++endColumn){
            if(arr[startColumn]<arr[endColumn]){
                q=arr[startColumn];
            }
            else{
                q=arr[endColumn];
            }
            if (endColumn - startColumn <= a and q <= c){
                int length = endColumn - startColumn;
                int height = q;
                int volume = b * length * height;
                if (volume > maxVolume){
                    maxVolume = volume;
                }
            }
        }
    }
    
    return maxVolume;
}
