#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20;

int n;
int ans;
int g[N][N];
int col[N], dg[2 * N + 1], udg[2 * N + 1];
int ccount;

void dfs(int u){
    if(u == n){
        ans ++;
        ccount ++;
        if(ccount > 3) return;

        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                if(g[i][j]) cout << j + 1<< " ";
            }
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i ++){
        if(!col[i] && !dg[u + i] && !udg[n - u + i]){
            g[u][i] = true;
            col[i] = dg[i + u] = udg[n - u + i] = true;
            dfs(u + 1);
            col[i] = dg[i + u] = udg[n - u + i] = false;
            g[u][i] = false;
        }
    }
}

int main (){
    cin >> n;
    
    dfs(0);

    cout << ans << endl;
    return 0;
}