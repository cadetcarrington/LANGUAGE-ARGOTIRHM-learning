#include <iostream>
#include <vector>

using namespace std;

vector<int> mat(vector<int> &A, int &B){
    int t = 0;
    vector<int> C;

    for (int i = 0; i < A.size(); i ++){
        t += A[i] * B;
        C.push_back(t % 10);
        t /= 10;
    }
    return C;
}

int main (){
    string a;
    int b;
    vector<int> A;

    cin >> a >> b;

    for (int i = a.size() - 1; i >= 0; i --){
        A.push_back(a[i] - '0');
    }
    // for (int i = b.size() - 1; i >= 0; i --){
    //     B.push_back(b[i] - '0');
    // }

    auto C = mat(A, b);

    for (int i = C.size(); i >= 0; i --){
        printf("%d", C[i]);
    }
    return 0;
}