#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int t, N;
	int c, d;

	scanf("%d", &t);

	for(int tc = 1; tc <= t; tc++) {
		int m = 0, ans = 0;
		scanf("%d", &N);
		for(int i = 1; i <= N; i++) {
			scanf("%d", &c);
			if(c == 0) {
				ans += m;
			}
			else if(c == 1) {
				scanf("%d", &d);
				m += d;
				ans += m;
			}
			else if(c == 2) {
				scanf("%d", &d);
				if(m < d) {
					m = 0;
				}
				else {
					m -= d;
				}
				ans += m;
			}
		}
		printf("#%d %d\n", tc, ans);
	}

    return 0;
}