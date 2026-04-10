#include <iostream>
#include <map>

using namespace std;

// const int N = 1000000010;

int n, q;
// int a[N];

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    map<int, int> a;
    for (int i = 1; i <= n; i ++){
        int w;
        cin >> w;
        a[w] = i;
    }
    cin >> q;
    while(q --){
        int s;
        cin >> s;
        auto i = a.find(s);
        if(i != a.end()){
            cout << i -> second << endl;
        }
        else {
            cout << 0 << endl;
        }
    }
    return 0;
}