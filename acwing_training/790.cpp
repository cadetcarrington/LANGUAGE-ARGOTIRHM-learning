#include <iostream>

using namespace std;

int main (){
    double n;
    cin >> n;

    double l = 0, r = n;
    
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