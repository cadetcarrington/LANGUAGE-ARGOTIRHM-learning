#include <iostream>

using namespace std;

const int N = 10010, M = 10010;

int a[N * M];

int main (){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i ++){
        for (int j = 0; j < m; j ++){
            cin >> a[i * m + j];
        }
    }

    int b[m * n];
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < m; j ++){
            b[j * n + i] = a[i * m + j];
            //cout << b[j * n + i] << endl;
        }
    }

    for (int i = 0; i < m; i ++){
        for (int j = 0; j < n; j ++){
            cout << b[i * n + j] << " ";
        }
        cout << endl;
    }
    return 0;
}