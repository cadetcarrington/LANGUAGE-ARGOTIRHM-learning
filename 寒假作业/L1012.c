#include <stdio.h>

int main (){
    int n;

    scanf("%d", &n);

    int ans = 1; 
    for (int i = 0; i < n; i ++){
        ans *= 2;
    }

    printf("2^%d = %d\n", n, ans);
    return 0;
}