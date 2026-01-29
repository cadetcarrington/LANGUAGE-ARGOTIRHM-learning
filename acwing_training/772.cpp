#include <iostream>
#include <cstring>

using namespace std;

char s[30] = {'a', 'b', 'c', 'd', 'e', 'f', 'g' ,'h', 'i','j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int num[26], n[30];
bool check = 0;
char a[100010];

int main (){

    cin.getline(a, 100010);

    for (int i = 0, len = strlen(a); i < len; i ++){
        num[a[i] - 'a'] ++;
    }

    for (int i = 0, len = strlen(a); i < len; i ++){
        if (num[a[i] - 'a']){
            cout << a[i] << endl;
            return 0;
        }
    }
    cout << "no" << endl;
    return 0;
}