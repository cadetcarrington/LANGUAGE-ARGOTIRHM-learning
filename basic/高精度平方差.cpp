#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

char a[110], b[110];
int na[110], nb[110], suma[110], ja[110], jb[110], sumb[110], sum[250];

int main()
{
    bool pd = 0;

    cin >> a >> b;

    if((a < b && strlen(a) == strlen(b)) || strlen(a) < strlen(b)) {//判断正负
	    swap(a, b);
	 	pd = true;
	}

    int lea = strlen(a);
    int leb = strlen(b);
    int len = max(lea, leb);
    if(a[0]== '-'){
  	    a[0] = '0';
    }
    if(b[0] == '-'){
  	    b[0] = '0';
    }

    for (int i = 1; i <= lea; i ++){
        na[i] = a[lea - i] - '0';
    }
    for (int j = 1; j <= leb; j ++){
        nb[j] = b[leb - j] - '0';
    }//输入int
    for (int i = 1; i <= len; i ++){
        suma[i] = suma[i] + na[i] + nb[i];
        if (suma[i] >= 10){
            suma[i + 1] = suma[i + 1] + suma[i] / 10;
            suma[i] = suma[i] % 10;
        }
    }//加法

    if (suma[len + 1]){
        len ++;
    }//进位

    for (int i = 1; i <= len; i ++){
//    if (na[i] < nb[i]){
//      na[i + 1] --;
//      na[i] += 10;
//    }
    sumb[i] = sumb[i] + na[i] - nb[i];
    if (sumb[i] < 0){
    	sumb[i + 1] --;
    	sumb[i] += 10;
    	//cout << sumb[i] << endl;
	}
    //cout << na[i] << nb[i] <<sumb[i] << endl;
  }//减法

    int lenj = len;
	if(sumb[len +1] != 0){
		pd = true;
	}
    while (sumb[lenj] == 0 && lenj != 1){
    lenj --;
    }//去0
    //int count = 1;
    if(lenj == 1){
    	pd = false;
	}
    for (int i = 1; i <= len; i ++){
        for (int j = 1; j <= lenj; j ++){
            sum[i + j - 1] = sum[i + j - 1] + suma[i] * sumb[j];
            //cout << i << " " << j << endl;
            //cout << sum[j] << endl;
            if (sum[i + j - 1] > 9){
                sum[i + j] = sum[i + j] + sum[i + j - 1] / 10;
                sum[i + j - 1] = sum[i + j - 1] % 10; 
            }
        }
    }

    int all = len + lenj;

    while (sum[all] == 0 && all != 1){
        all --; 
    }
    if(pd == true){
        cout << "-";
    }
    for (int i = all; i >= 1; i --){
        printf("%d", sum[i]);
    }
    printf("\n");

    return 0;
}