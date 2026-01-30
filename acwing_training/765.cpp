#include <iostream>

using namespace std;

int main (){
    string a;
    getline(cin, a);

    string b;

    for (auto c : a) b = b + c + ' ';

    b.pop_back();// 去掉最后的空格

    cout << b << endl;

    return 0;
}