#include <iostream>
#include "client.h"
using namespace std;

const int N = 10010;

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
            int id;
            if(cin >> id){
                client.Show(id);
            }
            else{
                client.Show();
            }
        }
    }
    
    cout << "Current Client Number: " << client.GetClientNum() << endl;
    return 0;
}