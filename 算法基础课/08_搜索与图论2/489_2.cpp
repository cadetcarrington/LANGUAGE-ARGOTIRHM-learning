#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 510;

int n, m;
int h[N], e[N], ne[N], idx;
int dist[N];
bool st[N];

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int dijkstra(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    pirority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});

    while(heap.size()){
        auto t = heap.top();
        heap.top();

        int ver = t.second, distance = t.first;
        if(st[ver]) continue;

        for(int i = h[ver]; i != -1; i = ne[i]){
            int j = e[i];
            if(dist[j]> distance + w[i]){
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    if(disdt[n] == 0x3f3f3f3f) return -1;

    return dist[n];
}

int main (){
    scanf("%d%d", &n, &m);

    memset(h, -1, size of h);

    while(m --){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
    }

    int = dijkstra();

    printf("%d\n", t);
}
