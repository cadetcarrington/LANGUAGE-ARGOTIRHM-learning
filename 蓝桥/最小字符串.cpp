#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100010;

int ans[N];
vector<int> ad;

int main()
{
  // 请在此输入您的代码
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    
    string a;
    cin >> a;
    for (int i = 0; i < s.size(); i ++){
        
    }
    for (int i = 0; i < a.size(); i ++){
        ad.push_back(a[i] - 'a');
    }
    sort(ad.begin(), ad.end());
    int count = 0;
    for (int i = 0; i < n; i ++){
        
        for (int j = count; j < m; j ++){
            if(ad[j] <= s[i]- 'a'){
                //cout << s[i] << ": " << ad[j] << " :";
                cout << char(ad[j] + 'a');
                //cout << endl;
                count ++;
            }
            else {
                break;
                //cout << endl << 1 << endl;
            }
        }
        cout << s[i];
    }
    //cout << endl << count;
    return 0;
}