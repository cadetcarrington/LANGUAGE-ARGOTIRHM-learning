#include <iostream>

using namespace std;

int a[10010], s;

int main (){
  int n, m;

  cin >> n >> m;

  int i = 1, count = 0;
  
  while (s < n - 1){
    if (a[i] == 0){
      count ++;
      if (count == m){
        a[i] = 1;
        count = 0;
        s ++;
      }
    }
    if (i == n){i = 0;}
    i ++;
  }

  for (int i = 1; i <= n; i ++){
    if (a[i]) continue;
    else cout << i << endl;
  }
  
  return 0;
}