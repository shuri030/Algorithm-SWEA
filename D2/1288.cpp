#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
 
using namespace std;
 
int num[7] = {1000000, 100000, 10000, 1000, 100, 10, 1};
int check[10];
int main()
{
    int t, n;
    scanf("%d", &t);
     
    for(int tc = 1; tc <= t; tc++) {
         
        int ch = 0, i = 0, tmp, cnt = 1, ans;
        scanf("%d", &n);
        tmp = n;
         
        while(1) {
            i = 0;
            while(1) {
                if(tmp / num[i] > 0) {
                    break;
                }
                i++;
            }
             
            for(int k = i; k <= 6; k++) {
                
                if(check[tmp / num[k]] == 0) {
                    check[tmp / num[k]] = 1;
                    ch++;
                    if(ch == 10) { break; }
                }
                tmp = tmp % num[k];
            }
             
            if(ch == 10) { ans = n * cnt; break; }
            cnt++;
            tmp = n * cnt;
        }
         
        printf("#%d %d\n", tc, ans);
        memset(check, 0, sizeof(check));
    }
    return 0;
}