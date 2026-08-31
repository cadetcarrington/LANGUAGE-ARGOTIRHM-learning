#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> div(vector<int> &A, int b, int &c){
    vector<int> C;
    c = 0; 
    for (int i = A.size() - 1; i >= 0; i --){
        c = c * 10 + A[i];
        C.push_back(c / b);
        c %= b;
    }

    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main (){
    string a;
    vector<int> A;
    int b, c;
    cin >> a >> b;

    for (int i = a.size() - 1; i >= 0; i --){
        A.push_back(a[i] - '0');
    }

    auto C = div(A, b, c);

    for (int i = C.size() - 1; i >= 0; i --){
        printf("%d", C[i]);
    }

    cout << endl << c << endl;
    return 0;
}