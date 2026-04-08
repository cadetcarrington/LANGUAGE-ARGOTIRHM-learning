#include <iostream>

using namespace std;

const int N = 10000010;
int a[N];
int n;

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    long double total = 1;
    for (int i = 0; i < n; i ++){
        cin >> a[i];
        total *= 3;
        //cout << total << endl;
    }

    total /= 3;
    long long ans = 0;
    for (int i = 0; i < n; i ++){
        ans += a[i] * total;
        //cout << ans << endl;
        total /= 3;
        ans %= 1000000007;
    }
    
    cout << ans << endl;
    // if(n == 1){
    //     cout << a[0] << endl;
    //     return 0;
    // }
    // else if(n == 2){
    //     cout << a[0] * 3 + a[1] << endl;
    //     return 0;
    // }
    // else if(n == 3){
    //     cout << a[0] * 9 + a[1] * 3 + a[2] << endl;
    // }
    return 0;
}