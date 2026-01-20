#include <stdio.h>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;

char a[N];

struct {
    int G = 0;
    int P = 0;
    int L = 0;
    int T = 0;
} s;

int main (){
    scanf("%s", a);
    
    int len = strlen(a);

    for (int i = 0; i < len; i ++){
        if(a[i] == 'G' || a[i] == 'g'){
            s.G ++;
        }
        else if(a[i] == 'P' || a[i] == 'p'){
            s.P ++;
        }
        else if(a[i] == 'L' || a[i] == 'l'){
            s.L ++;
        }
        else if(a[i] == 'T' || a[i] == 't'){
            s.T ++;
        }
    }

    int final = max(max(s.G, s.L), max(s.P, s.T));

    for (int i = 0; i < final; i ++){
        if(s.G != 0){
            printf("G");
            s.G --;
        }
        if(s.P != 0){
            printf("P");
            s.P --;
        }
        if(s.L != 0){
            printf("L");
            s.L --;
        }
        if(s.T != 0){
            printf("T");
            s.T --;
        }
    }
    printf("\n");
    return 0;
}