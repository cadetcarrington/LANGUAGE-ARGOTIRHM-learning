#include <iostream>

using namespace std;

int main (){
    string a;

    int flock = 0;
    while(getline(cin, a)){
        int mao = 0, dan = 0;
        for (int i = 0; i < (int)a.size(); i++){
            char c = a[i];
            if(flock == 0){
                if(c == '"' && !dan){
                    if (!mao) mao ++;
                    else mao --;
                    cout << c;
                    continue;
                }
                if(mao == 1){
                    cout << c;   
                }
                else {
                    // if(c == '/'){
                    //     if(dan == 1) dan ++;
                    //     if(!dan){
                    //         dan ++;
                    //     }
                    // }
                    // if(dan == 2){
                    //     cout << "#";
                    // }
                    if(!dan && i + 1 < (int)a.size() && c == '/' && a[i + 1] == '/'){
                        dan ++;
                        cout << c << a[i + 1];
                        i ++;
                        continue;
                    }
                    if(dan){
                        cout << "#";
                        continue;
                    }
                    if(i + 1 < (int)a.size() && c == '/' && a[i + 1] == '*'){
                        cout << "/*";
                        i ++;
                        flock = 1;
                        continue;
                    }

                    cout << c;
                }
            }
            else {
                if(i + 1 < (int)a.size() && c == '*' && a[i + 1] == '/'){
                    cout << "*/";
                    i ++;
                    flock = 0;
                }
                else {
                    cout << "#";
                }
            }
        }
        cout << endl;
    }

    return 0;
}