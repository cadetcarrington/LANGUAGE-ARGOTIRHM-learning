#include <iostream>

using namespace std;

const int N = 3010;

unsigned long long int a, s[N * N];
unsigned long long int t, n, m, q;

template <class T>
T getXorSum(T *begin, T *end) {
  T ret = 0;
  for (T *it = begin; it != end; ++it) ret ^= *it;
  return ret;
}



int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while(t --){
        cin >> n >> m >> q;
        for (int i = 1; i <= n; i ++){
            
            for (int j = 1; j <= m; j ++){
                cin >> a;
                s[i * m + j] = s[(i - 1) * m + j] + s[i * m + j - 1] - s[(i - 1) * m + j - 1] + a;
            }
            //int ans[q];
            //int qq = q;
        }
        unsigned long long int ans = 0;
        while(q --){
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            ans ^= s[x2 * m + y2] + s[(x1 - 1) * m + y1 - 1] - s[x2 * m + y1 - 1] - s[(x1 - 1) * m + y2];
        }
        cout << ans << endl;
    }
    return 0;
}