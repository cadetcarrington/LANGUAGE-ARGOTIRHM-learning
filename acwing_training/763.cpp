// #include <iostream>
// #include <string.h>

// using namespace std;

// int main (){
//     int n;
//     cin >> n;
    
//     for (int i = 0; i < n; i ++){
//         string a, b;
//         cin >> a >> b;
//         if (a == b){
//             cout << "Tie" << endl;
//         }
//         else if (a.size() == 6){
//             if(b.size() == 3){
//                 cout << "Player1" << endl;
//                 continue;
//             }
//             else {
//                 cout << "Player2" << endl;
//             }
//         }
//         else if (a.size() == 4){
//             if(b.size() == 6){
//                 cout << "Player1" << endl;
//             }
//             else {
//                 cout << "Player2" << endl;
//             }
//         }
//         else {
//             if(b.size() == 4) cout << "Player1" << endl;
//             else cout << "Player2" << endl;
//         }
//     }
//     return 0;
// }

#include <iostream>

using namespace std;

int main (){
    int n;
    cin >> n;

    while(n --){
        string a, b;
        cin >> a >> b;

        int x, y;
        if (a == "Hunter") x = 0;
        else if ( a == "Bear") x = 1;
        else x = 2;

        if (b == "Hunter") y = 0;
        else if (b == "Bear") y = 1;
        else y = 2;

        if(x == y) puts("Tie");
        else if(x == (y + 1) % 3) puts("Player1");
        else {
            puts("Player2");
        }
    }

    return 0;
}