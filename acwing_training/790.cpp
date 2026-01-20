#include <iostream>

using namespace std;

int main (){
    double n;
    cin >> n;

    double l = 0, r = n;
    if (r < 0){
        swap(l, r);
    }//如果n为负数，需要更改l和r的数值
    if(n > -1 && n < 1){
        l = -1;
        r = 1;
    }//对于在-1，1之间的数，需要特别的对待
    while (r - l >= 1e-8){
        double mid = (l + r ) / 2;
        if(mid * mid * mid >= n){
            r = mid;
        }
        else{
            l = mid;
        }
    }

    printf("%.6lf\n", l);
    return 0;
}