#include <cstdio>
#include <iostream>

using namespace std;

const int N = 110;

// int a[N];

struct school {
    int num;
    int p[11][10];
}a[N];

int main (){
    int n;
    cin >> n;

    for (int i = 0; i < n; i ++){
        scanf("%d", &a[i].num);
    }

    int maxfor = 0;

    for (int i = 0; i < n; i ++){
        if(a[i].num >= maxfor){
            maxfor = a[i].num;
        }
    }

    int cis = 1;
    for(int i = 0; i < maxfor; i ++){
        for (int j = 0; j < n; j ++){
            if(a[j].num >= maxfor){
                //这里还需要继续考虑
            }
        }
    }
    return 0;
}