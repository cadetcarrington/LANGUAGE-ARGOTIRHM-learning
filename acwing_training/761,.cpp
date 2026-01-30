#include <iostream>
#include <cstring>

using namespace std;

int main (){
    char a[101];

    fgets(a, 101, stdin);

    int nub = 0;
    for (int i = 0, len = strlen(a); i < len; i ++){
        if(a[i] >= '0' && a[i] <= '9'){
            nub ++;
        }
    }

    cout << nub << endl;
    
    return 0;
}