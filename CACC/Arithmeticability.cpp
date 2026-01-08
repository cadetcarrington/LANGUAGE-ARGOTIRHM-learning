#include <iostream>
#include <vector>

using namespace std;

int main (){
    int n, m;

    cin >> n >> m;
    
    vector<int> a(n + 10, 0);
    
    for (int i = 0; i < m; i ++){
        int act;
        cin >> act;

        if (act){
            int s, t, ans = 0;
            cin >> s >> t;

            for (int j = s; j <= t; j ++){
                ans += a[j];
            }
            cout  << ans << endl;
        }
        else {
            int s, t;
            cin >> s >> t;

            bool judge;
            cin >> judge;
            
            if (judge){
                int add;
                cin >> add;

                for (int j = s; j <= t; j ++){
                    if (a[j] % 2 != 0){
                        a[j] += add;
                    }
                }
            }
            else {
                int add;
                cin >> add;

                for (int j = s; j <= t; j ++){
                    if (a[j] % 2 == 0){
                        a[j] += add;
                    }
                }
            }
        }
    }
    return 0;
}