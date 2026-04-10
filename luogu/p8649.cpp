#include <iostream>

using namespace std;

const int N = 100010;

long long int a[N], s[N], b[N];
long long int n, k;

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i = 1; i <= n; i ++){
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }  
    
    int ans = 0;
    for (int i = 0; i <= n; i ++){
            ans += b[s[i] % k] ++;
    }

    cout << ans << endl;
    return 0;
}