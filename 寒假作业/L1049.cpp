#include <bits/stdc++.h>
using namespace std;

const int N = 110;
int biao[N];

struct school {
    int num;
    int p[N][10];
} a[N];

int main(){
    int n;
    cin >> n;

    for (int i = 0; i < n; i ++) {
        cin >> a[i].num;
        for (int j = 0; j < N; j ++) 
            for (int k = 0; k < 10; k ++) 
                a[i].p[j][k] = 0;
    }

    int maxfor = 0;
    for (int i = 0; i < n; i ++){
        maxfor = max(maxfor, a[i].num);
    }
    int count = 1;
    vector<int> team_idx(n, 0), pos_idx(n, 0);
    int remaining = 0;
    for (int i = 0; i < n; ++i) {
        remaining += a[i].num * 10;
    }

    while (remaining > 0){
        int active = 0, last = -1;
        for (int i = 0; i < n; ++i){
            if (team_idx[i] < a[i].num) { 
                active++; last = i; 
            }
        }

        if (active == 0) break;

        if (active == 1){
            if (count % 2 == 1) count++;
            int i = last;
            while (team_idx[i] < a[i].num){
                int t = team_idx[i];
                int k = pos_idx[i];
                a[i].p[t][k] = count;
                count += 2;
                remaining--;
                if (++pos_idx[i] == 10){ pos_idx[i] = 0; team_idx[i]++; }
            }
            break;
        }

        for (int i = 0; i < n && remaining > 0; i ++){
            if (team_idx[i] < a[i].num){
                int t = team_idx[i];
                int k = pos_idx[i];
                a[i].p[t][k] = count++;
                remaining--;
                if (++pos_idx[i] == 10){ pos_idx[i] = 0; team_idx[i]++; }
            }
        }
    }

    for (int i = 0; i < n; ++i){
        cout << "#" << (i+1) << endl;;
        for (int j = 0; j < a[i].num; j ++){
            for (int k = 0; k < 10; k ++){
                cout << a[i].p[j][k];
                if (k != 9){
                    cout << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}