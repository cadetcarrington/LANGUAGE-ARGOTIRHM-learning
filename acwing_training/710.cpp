#include <iostream>
#include <sstream>

using namespace std;

int main (){
    string a, b, c;
    getline(cin, a);
    cin >> b >> c;

    stringstream s(a);

    string str;
    while (s >> str){
        if (str == b) cout << c << " ";
        else cout << str << " ";
    }
    cout << endl;
    
    return 0;
}