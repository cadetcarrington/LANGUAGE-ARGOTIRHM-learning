#include <iostream>
#include <string.h>
#include <cstdio>

using namespace std;

int main (){
    char a[110], c[110];
    string b, d, b1;

    fgets(a, 110, stdin);
    cin.getline(a, 110);
    getline(cin, b);

    b1 = b + d;
    b1 += b; 

    cout << strlen(a) << endl;
    cout << strcmp(a, c) << endl;
    cout << b.empty() << endl;
    cout << b.size() << endl;

    printf("%s\n", a);
    puts(a);
    return 0;
}