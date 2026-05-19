#include <iostream>

using namespace std;

int a[1010][1010], b[1010][1010];
int n, m;

void insert(int x1, int y1, int x2, int y2){
    b[x1][y1] += 1;
    b[x2 + 1][y1] -= 1;
    b[x1][y2 + 1] -= 1;
    b[x2 + 1][y2 + 1] += 1;
}

int main (){
    cin >> n >> m;
    while(m --){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        insert(x1, y1, x2, y2);
    }
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j ++){
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}