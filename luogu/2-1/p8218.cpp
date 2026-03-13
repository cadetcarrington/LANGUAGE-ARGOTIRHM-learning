#include <iostream>
#include <cstdio>

using namespace std;

const int M = 10010;

int a[M], s[M];
int n, m;

int main (){
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i ++){
        int fir, sec;
        scanf("%d%d", &fir, &sec);
        printf("%d\n", s[sec] - s[fir - 1]);
    }

    return 0;
}