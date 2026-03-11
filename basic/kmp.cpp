#include <iostream>

using namespace std;

const int N = 100010, M = 1000010;

char p[N], s[M];

int a[M];
int n, m;

int main (){
    cin >> n >> p + 1 >> m >> s + 1;

    for (int i = 2, j = 0; i <= n; i ++){
        while (j && p[i] != p[j + 1]) j = a[j];
        if(p[i] == p[j + 1]) j ++;
        a[i] = j;
    }

    for (int i = 1, j = 0; i <= m; i ++){
        while (j && s[i] != p[j + 1]) j = a[j];
        if(s[i] == p[j + 1]){
            j ++;
        }
        if(j == n){
            printf("%d ", i - n + 1);
            j = a[j]
        }
    }
    return 0;
}