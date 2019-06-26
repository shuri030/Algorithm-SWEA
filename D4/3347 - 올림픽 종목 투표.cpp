#include <stdio.h>
#include <iostream>
using namespace std;

int N, M;
int A[1003];
int B[1003];
int cnt[1003];
int ans, ans_max;

int main()
{
    int tc;
    scanf("%d", &tc);

    for (int t = 1; t <= tc; t++) {
        scanf("%d %d", &N, &M);

        for(int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        for(int i = 0; i < M; i++) {
            scanf("%d", &B[i]);
        }


        for(int i = 0; i < M; i++) {
            int cost = B[i];
            for(int j = 0; j < N; j++) {
                if(A[j] <= cost) {
                    cnt[j]++;
                    if(ans_max < cnt[j]) { ans = j; ans_max = cnt[j]; }
                break;
                }
            }
        }

        printf("#%d %d\n", t, ans + 1);

        ans = 0; ans_max = 0;
        for(int i = 0; i < 1000; i++) {
            A[i] = 0; B[i] = 0; cnt[i] = 0;
        }
    }
    return 0;
}
