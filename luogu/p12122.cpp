#include <iostream>
#include <algorithm>

using namespace std;

int a[52];

int main (){
    for (int i = 1; i < 52; i ++){
        a[i] = i;
    }

    for (int i = 1; i <= 51; i ++){
        for (int j = i + 1; j <= 51; j ++){
            for (int k = 1; k <= 51; k ++){
                for (int l = k + 1; l <= 51; l ++){
                    swap(a[i], a[j]);
                    swap(a[k], a[l]);

                    sort(a + 1, a + 51);
                }
            }
        }
    }
    return 0;
}