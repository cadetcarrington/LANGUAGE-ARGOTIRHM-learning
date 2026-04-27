#include <iostream>
#include <cmath>

using namespace std;
int main (){
    long long int a;

    cin >> a;

    long long int min;
    for (long i  = 2; i < sqrt(a); i ++){
        if (a % i == 0){
            min = i;
            break;
        }
    }
    int max = a / min;
    cout << max << endl;
    return 0;
}