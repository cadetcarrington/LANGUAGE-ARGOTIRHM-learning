#include <iostream>
#include <cstring>

using namespace std;

const int N = 200003, null = 0x3f3f3f3f;

int h[N];

bool find(int x){
    int k = (x % N + N) % N;

    while(h[k] != null && h[k] != x){
        k ++;
        if(k == N) k = 0;
    }

    return k;
}

int main (){
    // 找质数
    // for (int i = 200000; ; i ++){
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

    memset(h, 0x3f, sizeof h);

    while(n --){
        char op[2];
        int x;
        cin >> op >> x;

        int k = find(x);
        if(* op == 'I') h[k] = x;
        else {
            if(h[k] != null) puts("Yes");
            else puts("No");
        }
    }

    return 0;
}