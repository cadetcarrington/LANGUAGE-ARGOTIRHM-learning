#include <iostream>

using namespace std;

const int N= 100010;

int n, m;
int p[N];
int sizee[N];

int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main (){
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i ++){
        p[i] = i;
        sizee[i] = 1;
    }

    while (m --){
        char op[5];
        int a, b;
        scanf("%s", op);
        
        if(op[0]='C') {
            scanf("%d%d", &a, &b);
            if(find(a) == find(b)) continue;
            p[find(a)] = find(b);
            sizee[find(b)] += sizee[find(a)];    
        }
        else if(op[1] = '1'){
            scanf("%d%d", &a, &b);
            if(find(a) == find(b)) puts("Yes");
            else puts("No"); 
        }
        else {
            scanf("%d", &a);
            scanf("%d", sizee[find(a)]);
        }
    }
    return 0;
}