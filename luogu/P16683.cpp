#include <iostream>

using namespace std;

const int N = 5e5 + 10;

int n, m;
long long int a[N];
long long sum;
int main (){
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        sum += a[i];
    }

    while(m --){
        int k;
        cin >> k;
        long long int ma = 0, ans1 = 0, mi = 0, ans2 = 0;
        for (int i = 1; i <= n; i ++){
            ma += (a[i] ^ k) - a[i];
            if(ma < 0) ma = 0;
            ans1 = max(ans1, ma);

            mi += (a[i] ^ k) - a[i];
            if(mi > 0) mi = 0;
            ans2 = min(ans2, mi);
        }
        cout << ans2 + sum << " " << ans1 + sum << endl;
    }

    return 0;
}