// #include <iostream>

// using std::cout, std::cin, std::max, std::endl;
// using namespace std;

// const int N = 1000010;

// int a[N], s[N];
// int n;

// int main (){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     cin >> n;
//     for (int i = 1; i <= n; i ++){
//         cin >> a[i];
//         s[i] = s[i - 1] + a[i];
//     }

//     int num = 0;
//     for (int i = 1; i <= n; i ++){
//         for (int j = i + 1; j <= n; j ++){
//             if((s[j] - s[i - 1]) % 7 == 0){
//                 num = max(num, j - i + 1);
//             }
//         }
//     }

//     cout << num << endl;
//     return 0;
// }

#include <iostream>

using namespace std;

const int N = 1000010;

int a[N], s[N];
int fir[7], las[7];
int n, ans = -1;

int main (){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        s[i] %= 7;
    }

    for (int i = 1; i <= n; i ++){
        las[s[i]] = i;
    }
    fir[0] = 0;
    for (int i = n; i >= 1; i --){
        fir[s[i]] = i;
    }

    for (int i = 0; i <= 6; i ++){
        ans = max(las[i] - fir[i], ans);
    }
    cout << ans << endl;
    return 0;
}