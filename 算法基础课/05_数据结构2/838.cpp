#include <iostream>
#include <cstdio>

using namespace std;

const int N = 10010;

int n, m, sizee;
int h[N];

void down(int u){
    int t = u;
    if(u * 2 <= sizee && h[u * 2] < h[t]) t = u * 2;
    if(u * 2 + 1 <= sizee && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if(u != t){
        swap(h[u], h[t]);
        down(t);
    }
}

int main (){
    scanf("%d", &n);
    for (int i = 0; i <= n; i ++){
        scanf("%d", &h[i]);
    }
    sizee = n;

    for (int i = n / 2; i <= n; i ++){
        down(i);
    }

    while(m --){
        printf("%d ", h[1]);
        h[1] = h[sizee];
        sizee --;
        down(1);
    }
    return 0;
}