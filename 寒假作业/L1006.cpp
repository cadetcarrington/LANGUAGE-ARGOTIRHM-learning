#include <stdio.h>
#include <math.h>

int main (){
    int n;

    scanf("%d", &n);

    int ch = sqrt(n);
    int len = 1, star = 0;

    for (int i = 2; i < ch + 2; i ++){
        if (n % i != 0){
            continue;
        }
        long long int mat = 1, malen = 0;
        for (int j = i; ; j ++){
            mat *= j;
            if (mat > n){
                break;
            }
            if (n % mat == 0){
                malen ++;
                if (malen > len){
                    len = malen;
                    star = i;
                }
            }
            else {
                break;
            }
        }
    }

    printf("%d\n", len);
    for (int i = star ; i < star + len - 1; i ++){
        printf("%d*", i);
    }
    printf("%d\n", star + len - 1);
    return 0;
}