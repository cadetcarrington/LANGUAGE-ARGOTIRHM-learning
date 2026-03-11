#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010, M = 10010;

long long a[N];
int n, m;

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i ++){
    scanf("%d", &a[i]);
  }
  sort(a, a + n);

  long long ans = 1e8;
  for(int i = 0; i < n - m; i ++){
    long long cu = a[i + m - 1] * a[i + m - 1] - a[i] * a[i];
    if(cu < ans){
      ans = cu;
    }
  }
  printf("%ld\n", ans);
  // 请在此输入您的代码
  return 0;
}