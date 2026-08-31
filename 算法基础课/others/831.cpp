#include <iostream>

using namespace std;

const int N = 10010, M = 100010;

int n, m;
int ne[M];
char p[N], s[M];

int main (){
    cin >> n >> p + 1 >> m >> s + 1;

    for (int i = 2, j = 0; i <= n; i ++){
        while(j && p[i] != p[j + 1]) j = ne[j]; printf("i: %d, p[i]: %c\nj: %d, p[j + 1]: %c", i, p[i], j, p[j + 1]);
        cout << endl;
        if(p[i] == p[j + 1]) j ++;
        cout << "j:" << j << endl;
        ne[i] = j;
        cout  << "ne" << i  << " " << ne[i] << endl;
    }

    for (int i = 1, j = 0; i < m; i ++){
        while(j && s[i] != p[j + 1]) j = ne[j];
        if(s[i] == p[j + 1]) j ++;
        if(j == n){
            printf("%d\n", i - n + 1);
            j = ne[j];
        }
    }
    return 0;
}