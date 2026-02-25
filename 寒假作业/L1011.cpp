#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int main (){
    string a, b;

    getline(cin, a);
    getline(cin, b);

    for(int i = 0; i < a.size(); i ++){
        bool judge = 0;
        for (int j = 0; j < b.size(); j ++){
            if(a[i] == b[j]){
                judge = 1;
                break;
            }
        }
        if(!judge){
            cout << a[i];
        }
    }
    cout << endl;
    return 0;
}

// int main (){
//     char a[10010], b[10010];

//     //cin.getline(cin, a);
//     scanf("%[^\n]", a);
//     scanf("%s", b);

//     int lena = strlen(a), lenb = strlen(b);

//     for (int i = 0; i < lena; i ++){
//         bool piont = true;
//         for(int j = 0; j < lenb; j ++){
//             if(a[i] == b[j]){
//                 piont = false;
//                 break;
//             }
//         }
//         if(piont){
//             cout << a[i];
//         }
//     }
//     cout << endl;

//     return 0;
// }