#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e3 + 10;

int main (){
    string a;
    cin >> a;
    int ans[N];
    int count = 0;
    for (int i = 0; i <= a.size(); i ++){
        if(a[i] <= '9' && a[i] >= '0'){
            ans[count ++] = a[i] - '0';
        }
    }
    
    sort(ans, ans + count);
    if(a[-- count] == 0) cout << 0 << endl;
    else {
        for(int i = count; i >= 0; i --){
            cout << ans[i];
        }
    }
}