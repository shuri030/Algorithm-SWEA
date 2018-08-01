#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
 
int prime[5] = {2, 3, 5, 7, 11};
int ans[5];
 
int main()
{
    int t, N, flag = 0;
     
    scanf("%d", &t);
 
    for(int tc = 1; tc <= t; tc++) {
        flag = 0;
        scanf("%d", &N);
 
        while(1) {
            for(int i = 0; i < 5; i++) {
                if(N % prime[i] == 0) {
                    ans[i]++;
                    N = N / prime[i];
                    if(N == 1) { flag = 1; break; }
                }
            }
            if(flag == 1) { break; }
        }
        printf("#%d ", tc);
        for(int i = 0; i < 5; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
        memset(ans, 0, sizeof(ans));
    }
 
    return 0;
}