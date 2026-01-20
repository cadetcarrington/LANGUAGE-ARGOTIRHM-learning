#include <iostream>

using namespace std;

const int N = 100000010;

int n;
int a[N];

void quick(int a[], int l, int r){
    if(l >= r){
        return;
    }
    
    int x = a[l + r >> 1], i = l - 1, j = r + 1;
    while (i < j){
        do i ++; while (a[i] < x);
        do j --; while (a[j] > x);
        if (i < j){
            swap(a[i], a[j]);
        }
    }
    
    quick(a, l, j);
    quick(a, j + 1, r);
}

int main (){
    int k;
    
    cin >> n >> k;
    for (int i = 0; i < n; i ++){
        scanf("%d", &a[i]);
    }
    
    quick(a, 0, n -1);
    
    printf("%d", a[k - 1]);
    return 0;
}