#include <iostream>

using namespace std;

const int N = 100010;

int a[N], s[N];
int n, m;

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
        s[i] += s[i - 1] + a[i];
    }


    cin >> m;
    while(m --){
        int l, r;
        cin >> l >> r;

        cout << s[r] - s[l - 1] << endl;
    }
    return 0;
}