#include <stdio.h>

struct {
    int num;
    char nam[10];
}a[60];

void f(int n, bool c){
    int l = 1, r = n;

    int i = 1, j =  r + 1;
    int count = 0;

    while (count < n / 2){
        do j --; while (c - a[j].num == 0 ||a[j].num >= 10);

        printf("%s %s\n", a[i].nam, a[j].nam);

        a[j].num = 100;
        j = r + 1;
        count ++;
        i ++;
        c = a[i].num;
    }
}

int main (){
    int n;
    
    scanf("%d", &n);

    for (int i = 1; i <= n; i ++){
        scanf("%d %s", &a[i].num, a[i].nam);
    }

    bool c = a[1].num;

    f(n, c);
    return 0;
}