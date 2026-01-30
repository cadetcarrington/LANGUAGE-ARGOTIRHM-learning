#include <iostream>
#include <cstring>

using namespace std;

int main (){
    string a;

    getline(cin, a);

    for (auto & c : a) {
        if(c >= 'a' && c <= 'z'){
            c = 'a' + (c - 'a' + 1) % 26;
        }
        else if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + 1) % 26;
        }
    }

    cout << a << endl;
    return 0;
}