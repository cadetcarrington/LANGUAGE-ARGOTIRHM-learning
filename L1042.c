#include <stdio.h>

int main (){
    char a[15];

    scanf("%s", a);

    for (int i = 6; i < 10; i ++){
        printf("%c", a[i]);
    }
    
    printf("-%c%c", a[0], a[1]);
    printf("-%c%c", a[3], a[4]);

    return 0;
}