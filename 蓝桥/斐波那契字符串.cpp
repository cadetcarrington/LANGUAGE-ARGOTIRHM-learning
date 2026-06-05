#include <iostream>

using namespace std;

const int N = 100010, M = 1e9 + 7;

long long int cn1[N], cn0[N], cnt[N];

int main()
{
    int t;
    cin >> t; 

    cn1[1] = 0;
    cn0[1] = 1;
    cn1[2] = 1;
    cn0[2] = 0;
    for (int i = 3; i <= N; i ++){
        cn1[i] = cn1[i - 1] + cn1[i - 2];
        cn0[i] = cn0[i - 1] + cn0[i - 2];
        cnt[i] = cnt[i - 1] + cnt[i - 2] + cn0[i - 1] * cn1[i - 2];
        cnt[i] %= M;
    }

    while(t --){
        int n; 
        cin >> n;
        cout << cnt[n] << endl;
    }
    return 0;
}