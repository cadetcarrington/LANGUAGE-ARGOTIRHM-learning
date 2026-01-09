#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>

using namespace std;

const int N = 110;

struct number{
    int a;
    int b;
    double num;
    bool c = 0;
}a[N];

bool cmp(number x, number y){
    return x.b < y.b;
}

int main (){
    int n;
    //char get[4];
    //double sum = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i ++){
        // scanf("%s", get);
        // if (get[0] == '-'){
        //     a[i].a = get[1] - '0';
        //     a[i].b = get[3] - '0';
        //     a[i].c = true;
        // }
        // else {
        //     a[i].a = get[0] - '0';
        //     //cout << a[i].a<< " ";
        //     a[i].b = get[2] - '0';
        //     //cout << a[i].b << endl;
        // }
        scanf("%d/%d", &a[i].a, &a[i].b);
        if(a[i].a < 0){
            a[i].c = true;
            a[i].a = -a[i].a;
        }
        a[i].num = 1.0 * a[i].a / a[i].b;
        //cout << a[i].num << endl;
        //sum += a[i].num;
        //cout << sum << endl;
    }

    // sum = int(sum);
    // printf("%d ", sum);

    sort(a, a + n, cmp);

    bool check = false;
    for (int i = n - 2; i >= 0; i --){
        if (a[n - 1].b % a[i].b != 0){
            check = true;
            break;
        }
    }

    long long int mu = 1;
    long long int fen = 0;

    if(!check){
        long long int final = 0;
        for (int i = 0; i < n; i ++){
            int mat = a[n - 1].b / a[i].b;
            a[i].a *= mat;

            if(a[i].c){
                final -= a[i].a;
            }
            else {
                final += a[i].a;
            }
        }

        // // if(final == a[n - 1].b){
        // //     return 0;
        // // }
        // if(final / a[n - 1].b != 0){
        //     cout << final / a[n - 1].b;
        //     final %= a[n - 1].b;
        //     if (final == 0){
        //         cout << endl;
        //         return 0;
        //     }
        //     cout << " ";
        // }

        // vector<bool> cou(final, true);
        // for (int i = 2; i <= final; i ++){
        //     if(!cou[i]) continue;
        //     for (int j = i; j < final; j += i){
        //         cou[j] = false;
        //     }
        //     if(final % i == 0 && a[n].b % i ==0){
        //         final /= i;
        //         a[n - 1].b /= i;
        //     }
        // }
        // cout << final << "/" << a[n - 1].b << endl;
        // return 0;
        mu = a[n - 1].b;
        fen = final;
    }
    else {
        mu = a[0].b;
        for(int i = 0; i < n; i ++){
            mu = lcm(mu, a[i].b);
        }

        int final= 0;
        for (int i = 0; i < n; i ++){
            int mat =  mu / a[i].b;
            a[i].a *= mat;

            if(a[i].c){
                final -= a[i].a;
            }
            else {
                final += a[i].a;
            }
        }
        fen = final;
    }

    if(fen == 0){
        cout << 0 << endl;
        return 0;
    }
    
    long long int com = gcd(abs(fen), mu);
    fen /= com;
    mu /= com;

    if(fen / mu != 0){
        if(fen % mu == 0){
            cout << fen / mu << endl;
            return 0;
        }
        cout << fen / mu << " ";
        fen %= mu;
    }

    cout << fen << "/" << mu << endl;
    return 0;
}