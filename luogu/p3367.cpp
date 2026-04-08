#include <iostream>

using namespace std;

const int N = 200010;
int p[N];
int n, m;

int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i ++){
        p[i] = i;
    }

    while(m --){
        int ch, a, b;
        cin >> ch >> a >> b;
        if(ch == 1){
            p[find(a)] = find(b);
        }
        else {
            if(find(a) == find(b)) cout << "Y" << endl;
            else cout << "N" << endl;
        }
    }
    return 0;
}