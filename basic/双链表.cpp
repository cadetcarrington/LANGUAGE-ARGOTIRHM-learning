#include <iostream>

using namespace std;

const int N = 100010;

int m;
int e[N], l[N], r[N], idx;

void init(){
    //0zuo,1you
    r[0] = 1, l[1] = 0;
    idx = 2;
}

//在k的右边插入x
void add(int k, int x){
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    l[r[k]] = idx;
    r[k] = idx;
}

void remove(int k){
    l[l[k]] = r[k];
    l[r[k]] = l[k];
}

int main (){
    
    return 0;
}