#include <iostream>

using namespace std;

const int N = 5000010;

int a[N], b[N];
int n, p;

void insert(int l, int r, int aa){
    b[l] += aa;
    b[r + 1] -= aa;
}

int main (){
    cin >> n >> p;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
        insert(i, i, a[i]);
    }
    while(p --){
        int l, r, na;
        cin >> l >> r >> na;

        insert(l, r, na);
    }

    int ans = N;
    for (int i = 1; i <= n; i ++){
        b[i] += b[i - 1];
        ans = min(b[i], ans);
    }

    cout << ans << endl;

    return 0;
}