#include <stdio.h>

int a[34] = {1,7,17,31,49,71,97,127,161,199,241,287,337,391,449,511,577,647,721,799,881,967,1057, 1000010};
int main (){
    int sum;
    char sign;
    int remain = 0;

    scanf("%d ", &sum);
    scanf("%c", &sign);

    for (int i = 0; i < 25; i ++){
        if (a[i] > sum){
            remain  = sum - a[i - 1];
            sum = a[i - 1];
            break;
        }
    }

    //printf("%d", sum);
    int half = (sum - 1) / 2;
    int ceng = 1, i = 3, sum1 = 3;

    while(sum1 != half){
        ceng ++;
        i += 2;
        sum1 += i;
    }
    //printf("%c", sign);
    // printf("%d %d %d", ceng, i, sum1);
    int c = 0;

    for (int j = 0; j < ceng; j ++){
        for (int k = 0; k < j; k ++){
            printf(" ");
            c = k;
            // printf("%d", c);
        }

        for (int k = 0; k < i; k ++){
            printf("%c", sign);
        }
        printf("\n");

        i -= 2;
    }

    c ++;
    for (int k = 0; k <= c; k ++){
        printf(" ");
    }
    
    printf("%c\n", sign);

    for (int j = 0; j < ceng; j ++){
        for (int k = ceng - j - 1; k > 0; k --){
            printf(" ");
        }

        i += 2;
        for (int k = 0; k < i; k ++){
            printf("%c", sign);
        }
        printf("\n");
    }
    printf("%d\n", remain);
    return 0;
}