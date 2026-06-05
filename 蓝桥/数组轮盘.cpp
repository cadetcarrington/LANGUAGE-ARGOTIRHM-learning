#include <iostream>
using namespace std;

int main (){
    int t;
    cin >> t;
    while(t --){
        int n, k;
        cin >> n >> k;
        k %= n;
        if(k == 0){
            cout << 0 << endl;
            continue;
        }
        
        if(n % 2 == 0){
            if(k % 2 == 0){
                cout << (n - k) / 2 << endl;
            }
            else {
                cout << -1 << endl;
            }
        }
        else{
            if(k % 2 == 0){
                cout << n - k / 2 << endl;
            }
            else{
                cout << (n - k) / 2 << endl;
            }
        }
    }
    return 0;
}