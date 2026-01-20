#include <stdio.h>

int main (){
    int h, m;

    scanf("%d:%d", &h, &m);

    if (h == 12 && m == 0){
        printf("Only 12:00.  Too early to Dang.\n");
        return 0;
    }

    if(h >= 12){
        if(m != 0){
            for(int i = 0; i < h - 12 + 1; i ++){
                printf("Dang");
            }
            printf("\n");
        }
        else {
            for (int i = 0; i < h - 12; i ++){
                printf("Dang");
            }
            printf("\n");
        }
    }
    else {
        if(h < 10){
           printf("Only 0%d:", h); 
        }
        else {
            printf("Only %d:", h);
        }
        if(m < 10){
            printf("0%d.  Too early to Dang.\n", m);
            return 0;
        }
        else {
            printf("%d.  Too early to Dang.\n", m);
        }
    }
    return 0;
}