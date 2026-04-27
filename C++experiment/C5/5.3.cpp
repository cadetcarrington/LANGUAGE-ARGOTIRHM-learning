#include <iostream>
#include <string.h>

using namespace std;

const int N = 10010, M = 10010;

int main (){
    //int n, m;
    char a[N], b[M];
    //cin >> n >> m;
    cin >> a >> b;
    int lena = strlen(a), lenb = strlen(b);

    char c[lena + lenb];
    for (int i = 0; i < lena; i ++){
        c[i] = a[i];
    }
    for (int i = 0; i < lenb; i ++){
        c[lena + i] = b[i];
    }
    c[lena + lenb] = '\0';

    cout << c << endl;
    return 0;
}