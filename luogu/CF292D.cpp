#include <iostream>

using namespace std;

const int N = 100010;

int p[N], a[N], b[N];
int sizee[N];
int n, m, k, sum;

int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i <= m; i ++){
        cin >> a[i] >> b[i];
    }
    cin >> k;

    while(k --){
        int c, d;
        cin >> c >> d;
        
        for (int i = 0; i <= n; i ++){
            p[i] = i;
        }
        sum = n;

        for(int i = 0; i <= c; i ++){
            if(find(a[i]) != find(b[i])){
                //p[find(a[i])] = find(b[i]);
                p[find(a[i])] = find(b[i]);
                sum --;
            }
        }

        for (int i = d + 1; i <= n; i ++){
            if(find(a[i]) != find(b[i])){
                p[find(a[i])] = find(b[i]);
                sum --;
            }
        }

        cout << sum << endl;

    }


    return 0;
}