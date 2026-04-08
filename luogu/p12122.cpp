#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int a[52];

int shichuanling(){
    int s = 0;
    for (int i = 1; i <= 51; i ++){
        for (int j = i + 1; j <= 51; j ++){
            if(a[j] < a[i]) s ++;
        }
    }
    return s;
}

int main (){
    for (int i = 1; i < 52; i ++){
        a[i] = i;
    }

    int ans = 0, n = 0;
    for (int i = 1; i <= 51; i ++){
        for (int j = i + 1; j <= 51; j ++){
            for (int k = 1; k <= 51; k ++){
                for (int l = k + 1; l <= 51; l ++){
                    swap(a[i], a[j]);
                    swap(a[k], a[l]);
                    n ++;
                    ans += shichuanling();
                    sort(a + 1, a + 52);
                }
            }
        }
    }
    cout << setprecision(10) << 1.0 * ans / n << endl;
    return 0;
}