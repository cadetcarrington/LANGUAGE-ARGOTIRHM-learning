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
    for (int i = 0; i <= n; i ++){
        cin >> a[i] >> b[i];
    }
    cin >> k;

    while(k --){
        int c, d;
        cin >> c >> d;
        
        for (int i = 0; i <= n; i ++){
            a[i] = i;
        }
        sum = n;

        for(int i = 0; i <= c; i ++){
            if(find(a[i] != b[i])){
                //p[find(a[i])] = find(b[i]);
                p[p[a[i]]] = p[b[i]];
                sum --;
            }
        }

        



    }


    return 0;
}