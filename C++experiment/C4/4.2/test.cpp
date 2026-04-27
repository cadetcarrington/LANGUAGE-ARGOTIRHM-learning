#include <iostream>
#include "client.h"
using namespace std;

const int N = 10010;

int sti(string s){
    int res = 0;
    for (int i = s.size() - 1; i >= 0; i--){
        res = res * 10 + (s[i] - '0');
    }
    return res;
}

int main (){
    int n, m;
    cout << "输入初始服务器数量和操作数量(I/O): ";
    cin >> n >> m;

    Client client(n);   

    cout << "Initial Client Number: " << client.GetClientNum() << endl;
    while (m --){
        char op[2];
        printf("I/O:");
        cin >> op;
        if (op[0] == 'I') {
            int id;
            string newName;
            cout << "输入服务器ID和新名称: ";
            cin >> id >> newName;
            client.ChangeServerName(id, newName);
        }
        else {
            string id;
            getchar();
            getline(cin, id);
            if(id[0]){
                int idd = sti(id);
                client.Show(idd);
            }
            else{
                cout << 1 << endl;
                client.Show();
            }
        }
    }

    cout << "Current Client Number: " << client.GetClientNum() << endl;
    return 0;
}