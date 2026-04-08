#include <iostream>

using namespace std;

const int N = 10010;

int s[N];
int n, m, p;

int find(int x){
    if(s[x] != x) s[x] = find(s[x]);
    return s[x]; 
}

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 0; i <= n; i ++){
        s[i] = i;
    }

    while(m --){
        int a, b;
        cin >> a >> b;
        s[find(a)] = find(b);
    }

    while(p --){
        int a, b;
        cin >> a >> b;
        if(find(a) == find(b)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}