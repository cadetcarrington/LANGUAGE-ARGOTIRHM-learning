#include <cstdio>

struct book {
    int number;
    bool check = false;
    char status;
    char time1[10];
    char time2[10];
} a[1010];

const int N = 110;

int sum[N], num[N];

int main (){
    int day;

    scanf("%d", &day);
    
    for (int j = 0; j < day; j ++){
        for (int k = 0; k < 1010; k ++){
            a[k].check = false;
        }
                
        for (int i = 0; i < 10000; i ++){
            int s;
            scanf("%d", &s);

            if(s == 0){
                scanf(" %c %s", &a[s].status, a[s].time1);
                if(num[j] == 0){
                    printf("0 0\n");
                }
                else if(sum[j]== 0){
                    printf("%d 0\n", num[j]);
                }
                else{ 
                    printf("%d %d\n", num[j], (int)((double)sum[j] / num[j] + 0.5));
                }
                break;
            }

            scanf(" %c", &a[s].status);

            if(a[s].check){
                if(a[s].status != 'E'){
                    scanf("%s", a[s].time1);
                    continue;
                } 
                scanf("%s", a[s].time2);
                num[j] ++;

                int hour1 = (a[s].time1[0] - '0') * 10 + (a[s].time1[1] - '0');
                int min1 = (a[s].time1[3] - '0') * 10 + (a[s].time1[4] - '0');
                int hour2 = (a[s].time2[0] - '0') * 10 + (a[s].time2[1] - '0');
                int min2 = (a[s].time2[3] - '0') * 10 + (a[s].time2[4] - '0');

                sum[j] += hour2 * 60 + min2 - hour1 * 60 - min1;
                a[s].check = false;
            }
            else if (a[s].status == 'S'){
                scanf("%s", a[s].time1);
                a[s].check = true;
            }
            else {
                scanf("%s", a[s].time1);
                continue;
            }
        }
    }
    return 0;
}