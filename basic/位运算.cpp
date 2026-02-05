#include <iostream>

using namespace std;

int main (){
    int n, m;
    cin >> n >> m;
    
    for (int i  = m; i >= 0; i --){
        cout << (n >> i & 1);
    }
    return 0;
}