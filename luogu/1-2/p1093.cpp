#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//typedef pair<int, int> PII;

struct PII{
    int sum;
    int chine;
    int number;
};

vector<PII> all;
int n;

int main (){
    scanf("%d", &n);
    int num = 0;
    while (n --){
        num ++;
        int a, b, c;
        cin >> a >> b >> c;
        all.push_back({a + b + c, a, num});
    }
    sort(all.begin(), all.end());

    
    return 0;
}