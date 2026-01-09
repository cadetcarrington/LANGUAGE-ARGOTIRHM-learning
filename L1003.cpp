#include <stdio.h>
#include <string.h>

int a[11];

int main (){
    char num[1010];

    scanf("%s", num);
    int len = strlen(num);
    for (int i = 0; i < len; i ++){
        int mid = num[i] - '0';

        switch (mid){
            case 1: 
                a[1] ++;
                break;
            case 2:
                a[2] ++;
                break;
            case 3:
                a[3] ++;
                break;
            case 4:
                a[4] ++;
                break;
            case 5:
                a[5] ++;
                break;
            case 6:
                a[6] ++;
                break;
            case 7:
                a[7] ++;
                break;
            case 8:
                a[8] ++;
                break;
            case 9:
                a[9] ++;
                break;
            case 0:
            a[0] ++;
            break;
        }
    }

    for (int i = 0; i < 10; i ++){
        if (a[i] == 0) continue;
        printf("%d:%d\n", i, a[i]);
    }
    // for (int i = 0; i < 10; i ++){
    //     int ans = 0, ansnum = 0;
    //         for (int j = 0; j < 10; j ++){
    //             if (a[j] > ans){
    //                 ans = a[j];
    //                 ansnum = j;
    //             }
    //         }
    //         if (ans == 0){
    //             break;
    //         }
    //         printf("%d:%d\n", ansnum, ans);
    //         a[ansnum] = 0;
    // }
    return 0;
}