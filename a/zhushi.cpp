#include <iostream>

using namespace std;

int main (){
    string a;
    cin >> a;

    int status = 0;
    while(getline(cin, a)){
        int mao = 0, chang = 0, dan = 0, xing = 0, xie = 0;
        for (auto c : a){
            if(c == '"'){
                if (!mao) mao ++;
                else mao --;
                continue;
            }
            if(mao == 1){
                cout << c;   
            }
            else if (!xing){
                // if(c == '/'){
                //     if(dan == 1) dan ++;
                //     if(!dan){
                //         dan ++;
                //     }
                // }
                // if(dan == 2){
                //     cout << "#";
                // }
                if(c == '/' && (c + 1) == '/'){
                    dan ++;
                    c ++;
                    continue;
                }
                if(dan){
                    cout << "#";
                    continue;
                }
                
            }
        }
    }

    return 0;
}