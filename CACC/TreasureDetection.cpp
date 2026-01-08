#include <iostream>

using namespace std;

int main (){
    int n, k;

    cin >> n >> k;

    int a[n + 10];

    for (int i = 1; i <= n; i ++){
        scanf("%d", &a[i]);
    }

    int round = n - k + 1;
    int ans[round + 10];
    int min1 = 10000000, min2 = 10000000;

    for (int i = 1; i <= round; i ++){
        for (int j = 1; j <= i; j ++){
            if (a[j] <= min1) min1 = a[j];
        }
        for (int j = n; j >= n - i - round; j --){
            if (a[j] <= min2) min2 = a[j];
        }

        ans[i] = abs(min1 - min2);
    }

    int finalans = 0;

    for (int i = 1; i <= round; i ++){
        if (a[i] >= finalans) finalans = a[i];
    }

    cout << finalans << endl;

    return 0;
}