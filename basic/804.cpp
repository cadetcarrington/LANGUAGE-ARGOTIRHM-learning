#include <iostream>
#include <cstring>

using namespace std;

const int N = 100003;

int h[N], idx, e[N], ne[N];

void insert(int x){
    int k = ((x % N) + N) % N;//哈希值

    e[idx] = x;
    ne[idx] = h[k];
    h[k] = idx ++;
}

bool find(int x){
    int k = ((x % N) + N) % N;
    for (int i = h[k]; i != -1; i = ne[i]){
        if(e[i] == k){
            return true;
        }
    }
    return false;
}

int main (){
    // 找质数
    // for (int i = 100000; ; i ++){
    //     bool flag = true;
    //     for (int j = 2; j * j <= i; j ++){
    //         if(i % j == 0){
    //             flag = false;
    //             break;
    //         }
    //         if(flag){
    //             cout << i << endl;
    //         }
    //     }
    // }

    int n;
    cin >> n;

    memset(h, -1, sizeof h);

    while(n --){
        char op[2];
        int x;
        cin >> op >> x;

        if(* op == 'I') insert(x);
        else {
            if(find(x)) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}