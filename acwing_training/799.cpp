#include <iostream>

using namespace std;

const int N = 100010;

int a[N], s[N];

int main (){
    int n;
    cin >> n;

    for (int i = 0; i < n; i ++){
        cin >> a[i];
    }

    int res = 0; 
    for (int i = 0, j = 0; i < n; i ++){
        s[a[i]] ++;
        
        while (s[a[i]] > 1){
            s[a[j]] --;
            j ++;
        }

        res = max(res, i - j + 1);
    }

    cout << res << endl;

    /*朴素做法
    for (int i = 0; i < n; i ++){
        for (itn j = 0; j < n; j ++){
            if(check(j, i)){
                res = max(res, i - j + 1);
            }
        }
    }*/
    

    return 0;
}