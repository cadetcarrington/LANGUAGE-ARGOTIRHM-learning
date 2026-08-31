#include <iostream>

using namespace std;

int main (){
    string str;

    getline(cin, str);

    for (int i = 0; i < str.size(); i ++){

        int j = i; 
        while (j < str.size() && str[j] != ' '){
            j ++;
        }

        for (int k = i; k < j; k ++){
            cout << str[k];
        }
        cout << endl;

        i = j;
    }

    return 0;
}
