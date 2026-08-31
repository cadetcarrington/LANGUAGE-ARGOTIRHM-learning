#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n;
int a[N], f[N]; 

int main (){
    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
    }

    for (int i = 1; i <= n; i ++){
        f[i] = 1;
        for (int j = 1; j <= n; j ++){
            if(a[i] < a[j]){
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i ++){
        ans = max(f[i], ans);
    }

    cout << ans << endl;
    return 0;
}