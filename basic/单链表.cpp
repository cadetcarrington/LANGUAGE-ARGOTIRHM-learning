#include <iostream>

using namespace std;

const int N = 100010;
//head:头节点下标
//e[i]:节点i的值
//ne[i]:节点i的下一个指针
//存储当前使用到的点
int head, e[N], ne[N], idx;

void index(){
    head = -1;
    idx = 0;
}

void add_to_head(int x){
    e[idx] = x;
    ne[idx] = head;
    head = idx;
    idx ++;
}

void add(int x, int k){
    e[idx] = x;
    ne[idx] = ne[k];
    ne[k] = idx;
    idx ++;
}

//删下标k后面的点
void remove(int k){   
    ne[k]= ne[ne[k]];
}

int main (){
    int n;
    cin >> n;

    index();

    while(n --){
        char sign;
        cin >> sign;
        if(sign = 'H'){
            int x;
            cin >> x;
            add_to_head(x);
        }
        else if(sign == 'D'){
            int k;
            cin >> k;
            if(k == 0) index;
            else {
                remove(k - 1);
            }
        }
        else{
            int k, x;
            cin >> k >> x;
            add(x, k - 1);
        }
    }

    for (int i = head; i != -1; i = ne[i])
        cout << e[i] << " ";

    cout << endl;
    return 0;
}