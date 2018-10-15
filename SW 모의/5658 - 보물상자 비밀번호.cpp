#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <stack>
#include <math.h>
#include <string.h>
#include <set>
#include <functional>
#include <algorithm>
using namespace std;

int N, K;
char number[30];
set <int> s;

int main()
{
	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++) {
		scanf("%d %d", &N, &K);

		//input
		for (int i = 1; i <= N; i++) {
			scanf(" %1c", &number[i]);
		}

		for (int i = 0; i <= (N / 4) - 1; i++) {
			//계산해서 넣기
			int j = 1;
			while (j < N) {
				int sum = 0;
				int upp = (N / 4) - 1; //몇승?

				//자릿수대로 10진수로 변환
				for (int k = j; k <= j + (N / 4) - 1; k++) {
					//숫자면
					if (number[k] - '0' >= 0 && number[k] - '0' <= 9) {
						sum = sum + pow(16, upp) * (number[k] - '0');
					}
					else {
						sum = sum + pow(16, upp) * (number[k] - 'A' + 10);
					}
					upp--;
				}

				s.insert(sum);
				j = j + (N / 4);
			}
			//회전
			char tmp = number[N];
			for (int k = N; k >= 2; k--) {
				number[k] = number[k - 1];
			}
			number[1] = tmp;


		}

		//set = ans
		int ans[30] = { 0, };
		int i = 0;
		for (auto iter = s.begin(); iter != s.end(); iter++) {
			ans[i] = *iter;
			i++;
		}
		sort(ans, ans + N, greater<int>());

		printf("#%d %d\n", tc, ans[K - 1]);
		s.clear();
		memset(number, 0, sizeof(number));
	}

	return 0;

}
