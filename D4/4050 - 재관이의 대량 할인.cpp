#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <functional>
#define C_MAX 100005
using namespace std;

int N;
int C[C_MAX];
int ans;

int main()
{
    int tc;
    scanf("%d", &tc);

    for (int t = 1; t <= tc; t++) {
        scanf("%d", &N);

        for(int i = 0; i < N; i++) {
            scanf("%d", &C[i]);
        }

        sort(C, C + N, greater<int>()); //내림차순

        for(int i = 0; i < N; i++) {
            if((i + 1) % 3 != 0) {
                ans += C[i];
            }
        }
        printf("#%d %d\n", t, ans);
        ans = 0;
        for(int i = 0; i < N; i++) {
            C[i] = 0;
        }
    }
    return 0;
}
