#include <iostream>

using namespace std;

int main (){
    long long a = 8100178706957568;
    for (int j = 11; j <= 36; j ++){
        a = 8100178706957568;
        for (int i = a; i < (8100178706957568 / j) + 1; i ++){
            if(a % j >= 10) {
                cout << j << endl;
                break;
            }
            else a /= j;
        }
    }
    
    return 0;
}