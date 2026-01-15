#include <iostream>
#include <cstdio>

using namespace std;

int main (){
    int n;

    scanf("%d", &n);

    long long int temp = 1;
    int num = 0;
    
    while (temp < n){
        temp = temp * 10 + 1;
        num ++;
    }

    while (1){
        printf("%lld", temp / n);

        temp %= n;

        if(temp == 0){
            num ++;
            break;
        }

        temp = temp * 10 + 1;
        num ++;
    }

    cout << num << endl;
    return 0;
}