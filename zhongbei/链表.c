#include <stdio.h>

const int N = 10010;

struct sxu {
    int num;
    int next;
    //int be;
}a[N];

int n, m, idx = 1;

void init(){
    for (int i = 1; i <= n; i ++){
        scanf("%d", &a[idx].num);
        a[idx].next = i + 1;
        idx ++;
    }
    a[idx].next = 0;
    n ++;
}

void put(int aa, int b){
    a[idx].num = aa;
    a[idx].next = a[b].next;
    a[b].next = idx;
    idx ++;
    n ++;
}

void puth(int aa){
    a[idx].num = aa;
    a[idx].next = a[0].next;
    a[0].next = idx;
    idx ++;
    n ++;
}

int query(int qa){
    for (int i = 0; i < idx; i ++){
        if(a[i].next == qa - 1){
            return a[a[i].next].num;
        }
    }
}

void remove(int aa){
    a[aa].next = a[a[aa].next].next;
    n --;
}

void print(){
    int i = 0;
    printf("total:%d\n", n --);
    while(a[i].next != 0){
        i = a[i].next;
        printf("%d ", a[i].num);
    }
}

int main (){  
    scanf("%d", &n);
    a[0].next = 1;
    init();
    
    int puta, putb;
    scanf("%d%d", &puta, &putb);

    if(putb == 0){
        puth(puta);
    }
    else put(puta, putb);

    int qa;

    scanf("%d", &qa);

    printf("%d\n", query(qa));

    int ra;
    scanf("%d", &ra);

    remove(ra);

    print();
    return 0;
}