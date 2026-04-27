#include <iostream>

using namespace std;

int main (){
    int n, m;
    int * a, * b;
    cin >> n >> m;

    a = new int[n * m];
    b = new int[m * n];
    for (int i = 0; i < n; i ++){
        for (int j = 0; j < m; j ++){
            cin >> * (a + i * m + j);
            * (b + j * n + i) = * (a + i * m + j);
        }
    }

    for (int i = 0; i < m; i ++){
        for (int j = 0; j < n; j ++){
            cout << *(b + i * n + j) << " ";
        }
        cout << endl;
    }

    delete [] a;
    delete [] b;
    
    return 0;
}