#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef pair<long long, long long> PII;

const long long int N = 2e5 + 10;
long long int n, m, s;
long long int w[N], v[N];
long long int s1[N], s2[N];
long long ans = 1000010, y;

vector<PII> q;

bool ch(long long  ww){
    y = 0;
    memset(s1, 0, sizeof(s1));  
	memset(s2, 0, sizeof(s2));

    for(int i = 1; i <= n; i ++){
        if(w[i] >= ww){
            s1[i] = s1[i - 1] + 1;
            s2[i] = s2[i - 1] + v[i];
        }
        else{
            s1[i] = s1[i - 1];
            s2[i] = s2[i - 1];
        }
    }
    for (int i = 1; i <= m; i ++){
        y += (s1[q[i - 1].second] - s1[q[i - 1].first - 1]) * (s2[q[i - 1].second] - s2[q[i - 1].first - 1]);
    }
    if(y > s){
        return 1;
    }
    else {
        return 0;
    }
}

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    for (int i = 1; i <= n; i ++){
        cin >> w[i] >> v[i];
    }
    for(int i = 1; i <= m; i ++){
        int l, r;
        cin >> l >> r;
        q.push_back({l, r});
    }

    int l = 1;
	int r = 2000010;

    ans = s;

    while(l <= r){
        long long mid = l + (r - l) / 2;
        if(ch(mid)){
            l = mid + 1;
        }
        else r = mid - 1;
        ans = min(ans, llabs(s - y));
    }
    cout << ans << endl;
    return 0;
}