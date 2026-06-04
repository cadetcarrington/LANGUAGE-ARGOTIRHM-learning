#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

int n;
int ans;
int g[N][N];
int col[N], dg[2 * N + 1], udg[N];

void dfs(int u){
    if(u == n){
        ans ++;
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                if(g[i][j]) cout << j << " ";
            }
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i ++){
        if(!col[i] && !dg[u + i] && !udg[n - u + i]){
            g[N][N] = true;
            col[i] = dg[i + u] = udg[n - u + i] = true;
            dfs(u + 1);
            col[i] = dg[i + u] = udg[n - u + i] = false;
            g[N][N] = true;
        }
    }
}

int main (){
    cin >> n;
    
    dfs(1);

    cout << ans << endl;
    return 0;
}