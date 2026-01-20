#include <iostream>
#include <algorithm>
using namespace std;
// int divide(int x[], int num){
//     if ( num <= 1){
//         return 0;
//     }
//     int mid = num / 2;
    
// }
// int max(int a, int b){
//     return (a > b) ? a : b;
// }
void divide(int x[], int l, int r){
    if (r - l == 1){
      //  cout << "l" << l  << " " << " r" << r << endl;
        cout << x[l] << " " << x[r] << endl;
        sort(x + l, x + r + 1);
        cout << x[l] << " " << x[r] << endl;
        return ;
    }
    int mid  = l + (r - l)/ 2;
    // int left = 
    divide(x, l, mid);
    // int right = 
    divide(x, mid, r);
    // int maxs = max(left, right);
    
}
int main (){
    int a[8]{7,3,5,1,8,6,2,4};
    divide(a, 0, 8);
    //sort(a + 2, a + 4);
    for (int i = 0; i < 8; i++){
        cout << a[i] << " ";
    }
    return 0;
}