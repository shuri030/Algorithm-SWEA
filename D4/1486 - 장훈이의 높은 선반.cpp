#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <algorithm>
using namespace std;

int N, B;
int num[21];
int ans;

void go(int i, int sum)
{
    if(i > N) {
        if((ans >= sum - B) && (sum >= B))  {
            ans = sum - B;
        }
        return;
    }

    //포함
    go(i + 1, sum + num[i]);

    //미포함
    go(i + 1, sum);

}

int main()
{
    int tc;
    scanf("%d", &tc);

    for(int t = 1; t <= tc; t++) {
        ans = INT_MAX / 2;
        
        scanf("%d %d", &N, &B);

        for(int i = 0; i < N; i++) {
            scanf("%d", &num[i]);
        }

        go(0, 0);

        printf("#%d %d\n", t, ans);
        memset(num, 0, sizeof(num));
    }

    return 0;
}
