#include <iostream>

using namespace std;

const int N = 200010;

int a[N], s[N], b[N];
int n, k, q;

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> q;
    for (int i = 0; i < n; i ++){
        int aa, bb;
        cin >> aa >> bb;

        a[aa] ++; a[bb + 1] --;

        // for (int j = aa; j <= bb; j ++){
        //     a[j] ++;
        //     if(a[j] == k) {
        //         b[j] ++;
        //         //s[j] = s[j - 1] + b[j];
        //     }
        // } 
    }

    for (int j = 0; j <= 200000; j ++){
        b[j] = b[j - 1] + a[j];
        if(b[j] >= k){
            s[j] = s[j - 1] + 1;
        }
        else {
            s[j] = s[j - 1];
        }
        
    }

    while(q --){
        int l, r;
        cin >> l >> r;

        cout << s[r] - s[l - 1] << endl;
    }
    return 0;
}