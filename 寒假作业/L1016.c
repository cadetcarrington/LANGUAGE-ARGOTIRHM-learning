#include <stdio.h>

int main (){
    int n;

    scanf("%d", &n);

    char a[n + 1][28];
    for (int i = 1; i <= n; i ++){
        scanf("%s", a[i]);
    }

    short sign = 1;
    for (int i = 1; i <= n; i ++){
        short internal = 0;
        for(int j = 0; j < 17; j ++){
            if(a[i][j] - '0' < 0 || a[i][j] - '0' > 9){
                sign = 0;
                internal = 1;
                printf("%s\n", a[i]);
                break;
            }
        }
        if(!internal){
            int check = 7 * (a[i][0] - '0') + 9 * (a[i][1] - '0') + 10 * (a[i][2] - '0') + 5 * (a[i][3] - '0') + 8 * (a[i][4] - '0') + 4 * (a[i][5] - '0') + 2 * (a[i][6] - '0') + (a[i][7] - '0');
            check += 6 * (a[i][8] - '0') + 3 * (a[i][9] - '0') + 7 * (a[i][10] - '0') + 9 * (a[i][11] - '0') + 10 * (a[i][12] - '0') + 5 * (a[i][13] - '0') + 8 * (a[i][14] - '0') + 4 * (a[i][15] - '0') + 2 * (a[i][16] - '0');
            check %= 11;
            // if(check != a[i][18]){
            //     sign = 0;
            //     printf("%s\n", a[i]);
            // }
            short pan = 0;
            switch (check){
                case 0 :
                    if(a[i][17] - '0' != 1){
                        pan = 1;
                    }
                    break;
                case 1:
                    if(a[i][17] - '0' != 0){
                        pan = 1;
                    }
                    break;
                case 2:
                    if(a[i][17] != 'X'){
                        pan = 1;
                    }
                    break;
                case 3:
                    if(a[i][17] != '9'){
                        pan = 1;
                    }
                    break;
                case 4:
                    if(a[i][17] != '8'){
                        pan = 1;
                    }
                    break;
                case 5:
                    if(a[i][17] != '7'){
                        pan = 1;
                    }
                    break;
                case 6:
                    if(a[i][17] != '6'){
                        pan = 1;
                    }
                    break;
                case 7:
                    if(a[i][17] != '5'){
                        pan = 1;
                    }
                    break;
                case 8:
                    if(a[i][17] != '4'){
                        pan = 1;
                    }
                    break;
                case 9:
                    if(a[i][17] != '3'){
                        pan = 1;
                    }
                    break;
                case 10:
                    if(a[i][17] != '2'){
                        pan = 1;
                    }
                    break;
            }

            if(pan){
                printf("%s\n", a[i]);
                sign = 0;
            }
        }
    }

    if(sign){
        printf("All passed\n");
    }
    return 0;
}